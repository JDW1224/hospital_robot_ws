#!/usr/bin/env python3
"""
병원 휠체어 웹 서버 노드
- 핸드폰(아이폰 Safari) → 음성/버튼 입력 → POI 선택
- DestinationParser로 "301호" → "301" 변환
- /navigate_to_poi (String) 발행 → goal_sender가 받아 Nav2로 주행
- /nav_state (String, JSON) 구독 → WebSocket으로 핸드폰에 실시간 상태 표시

구조:
  [아이폰] --HTTPS/WSS--> [노트북 web_server] --ROS2 DDS--> [젯슨 goal_sender]

실행:
  ros2 launch hospital_robot_web web.launch.py
  또는
  ros2 run hospital_robot_web web_server

접속:
  https://<노트북IP>:8443  (아이폰 Safari)
  ⚠️ 자체서명 인증서라 "안전하지 않음" 경고 뜸 → 무시하고 진행
"""
import os
import json
import threading
import asyncio

import rclpy
from rclpy.node import Node
from std_msgs.msg import String, Bool

import uvicorn
from fastapi import FastAPI, WebSocket, WebSocketDisconnect
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles

from hospital_robot_poi.poi_manager import POIManager
from hospital_robot_poi.destination_parser import DestinationParser


# ── 경로 ──
PKG_WEB_DIR = os.path.dirname(os.path.abspath(__file__))
# 설치 후엔 share 폴더의 web/ 사용, 개발 중엔 소스의 web/ 사용
WEB_DIR_CANDIDATES = [
    os.path.expanduser('~/hospital_robot_ws/src/hospital_robot_web/web'),
    os.path.join(PKG_WEB_DIR, '..', 'web'),
]
WEB_DIR = next((p for p in WEB_DIR_CANDIDATES if os.path.isdir(p)), WEB_DIR_CANDIDATES[0])

POI_YAML = os.path.expanduser(
    '~/hospital_robot_ws/src/hospital_robot_poi/poi/destinations.yaml'
)

CERT_DIR = os.path.expanduser('~/hospital_robot_ws/certs')
CERT_FILE = os.path.join(CERT_DIR, 'cert.pem')
KEY_FILE = os.path.join(CERT_DIR, 'key.pem')


class WebServerNode(Node):
    def __init__(self):
        super().__init__('web_server_node')

        # POI 매니저 + 파서
        self.poi_mgr = POIManager(POI_YAML)
        self.parser = DestinationParser(self.poi_mgr)
        self.get_logger().info(f'POI {self.poi_mgr.count()}개 로드: {self.poi_mgr.get_ids()}')

        # ROS 발행/구독
        self.pub_goal = self.create_publisher(String, '/navigate_to_poi', 10)
        self.pub_cancel = self.create_publisher(String, '/cancel_navigation', 10)
        self.pub_estop = self.create_publisher(Bool, '/emergency_stop', 10)
        self.sub_state = self.create_subscription(
            String, '/nav_state', self.on_nav_state, 10
        )

        # 최신 상태 저장 (WebSocket으로 전달)
        self.latest_state = {'state': 'IDLE', 'goal_id': '', 'goal_name': ''}

        # WebSocket 연결된 클라이언트들에게 상태 푸시할 콜백 (FastAPI 쪽에서 등록)
        self.ws_broadcast = None
        self.event_loop = None

        self.get_logger().info('web_server_node 시작됨')

    def send_goal(self, poi_id: str):
        """POI ID를 /navigate_to_poi로 발행"""
        msg = String()
        msg.data = poi_id
        self.pub_goal.publish(msg)
        self.get_logger().info(f'🚀 목적지 발행: {poi_id}')

    def send_cancel(self):
        msg = String()
        msg.data = 'cancel'
        self.pub_cancel.publish(msg)
        self.get_logger().info('🛑 취소 발행')

    def send_estop(self, on: bool):
        """비상정지 토글을 /emergency_stop(Bool)로 발행. on=True 정지, False 해제."""
        msg = Bool()
        msg.data = bool(on)
        self.pub_estop.publish(msg)
        self.get_logger().info(f'🛑 비상정지 {"ON" if on else "해제"} 발행')

    def on_nav_state(self, msg: String):
        """goal_sender의 /nav_state 수신 → WebSocket으로 전파"""
        try:
            self.latest_state = json.loads(msg.data)
        except Exception:
            self.latest_state = {'state': msg.data, 'goal_id': '', 'goal_name': ''}

        # WebSocket으로 푸시
        if self.ws_broadcast and self.event_loop:
            asyncio.run_coroutine_threadsafe(
                self.ws_broadcast(self.latest_state), self.event_loop
            )

    def resolve_poi(self, text: str):
        """음성/텍스트 → POI ID. 못 찾으면 None"""
        return self.parser.parse(text)


# ── FastAPI 앱 ──
app = FastAPI()
ros_node: WebServerNode = None
active_websockets = set()


@app.get('/', response_class=HTMLResponse)
async def index():
    index_path = os.path.join(WEB_DIR, 'index.html')
    if os.path.exists(index_path):
        with open(index_path, 'r', encoding='utf-8') as f:
            return f.read()
    return HTMLResponse('<h1>index.html을 찾을 수 없습니다</h1>', status_code=404)


@app.get('/api/pois')
async def get_pois():
    """등록된 POI 목록 (핸드폰 버튼 생성용)"""
    pois = ros_node.poi_mgr.get_all()
    # 경유점(waypoint)은 목적지 버튼에서 제외 — 방(room)만 노출
    return {'pois': [{'id': p['id'], 'name': p['name']}
                     for p in pois if p.get('type', 'room') == 'room']}


@app.websocket('/ws')
async def websocket_endpoint(ws: WebSocket):
    await ws.accept()
    active_websockets.add(ws)
    ros_node.get_logger().info('📱 WebSocket 연결됨')

    # 연결 즉시 현재 상태 전송
    await ws.send_json({'type': 'state', **ros_node.latest_state})

    try:
        while True:
            data = await ws.receive_json()
            await handle_ws_message(ws, data)
    except WebSocketDisconnect:
        active_websockets.discard(ws)
        ros_node.get_logger().info('📱 WebSocket 연결 해제')
    except Exception as e:
        active_websockets.discard(ws)
        ros_node.get_logger().warn(f'WebSocket 오류: {e}')


async def handle_ws_message(ws: WebSocket, data: dict):
    """핸드폰에서 온 메시지 처리"""
    msg_type = data.get('type')

    if msg_type == 'voice' or msg_type == 'command':
        # 음성 인식 결과 또는 버튼 클릭
        text = data.get('text', '').strip()
        ros_node.get_logger().info(f'📥 입력 수신: "{text}"')

        poi_id = ros_node.resolve_poi(text)
        if poi_id:
            poi = ros_node.poi_mgr.get(poi_id)
            ros_node.send_goal(poi_id)
            await ws.send_json({
                'type': 'ack',
                'success': True,
                'poi_id': poi_id,
                'poi_name': poi['name'],
                'message': f'{poi["name"]}(으)로 이동합니다',
            })
        else:
            await ws.send_json({
                'type': 'ack',
                'success': False,
                'message': f'"{text}"에 해당하는 장소를 찾지 못했습니다',
            })

    elif msg_type == 'cancel':
        ros_node.send_cancel()
        await ws.send_json({
            'type': 'ack', 'success': True, 'message': '주행을 취소했습니다',
        })

    elif msg_type == 'estop':
        # 비상정지 토글: data.on True=정지, False=해제
        on = bool(data.get('on', True))
        ros_node.send_estop(on)
        await ws.send_json({
            'type': 'ack', 'success': True,
            'message': '비상정지' if on else '비상정지 해제',
        })


async def broadcast_state(state: dict):
    """모든 연결된 핸드폰에 상태 전파"""
    dead = set()
    for ws in active_websockets:
        try:
            await ws.send_json({'type': 'state', **state})
        except Exception:
            dead.add(ws)
    for ws in dead:
        active_websockets.discard(ws)


def ros_spin(node):
    """ROS2 스핀 (별도 스레드)"""
    rclpy.spin(node)


def main(args=None):
    global ros_node

    rclpy.init(args=args)
    ros_node = WebServerNode()

    # ROS2 스핀을 별도 스레드에서
    ros_thread = threading.Thread(target=ros_spin, args=(ros_node,), daemon=True)
    ros_thread.start()

    # FastAPI 이벤트 루프 + 브로드캐스트 콜백 등록
    @app.on_event('startup')
    async def on_startup():
        ros_node.event_loop = asyncio.get_event_loop()
        ros_node.ws_broadcast = broadcast_state
        ros_node.get_logger().info('FastAPI 시작, WebSocket 브로드캐스트 등록됨')

    # HTTPS (인증서 있으면) 또는 HTTP
    use_https = os.path.exists(CERT_FILE) and os.path.exists(KEY_FILE)

    if use_https:
        ros_node.get_logger().info('🔒 HTTPS 모드 (포트 8443)')
        ros_node.get_logger().info(f'   접속: https://<노트북IP>:8443')
        uvicorn.run(
            app, host='0.0.0.0', port=8443,
            ssl_certfile=CERT_FILE, ssl_keyfile=KEY_FILE,
            log_level='warning',
        )
    else:
        ros_node.get_logger().warn('⚠️ 인증서 없음 → HTTP 모드 (포트 8000)')
        ros_node.get_logger().warn('   아이폰 마이크는 HTTPS 필요! 인증서 생성하세요.')
        ros_node.get_logger().info(f'   접속: http://<노트북IP>:8000')
        uvicorn.run(app, host='0.0.0.0', port=8000, log_level='warning')


if __name__ == '__main__':
    main()