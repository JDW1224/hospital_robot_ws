#!/usr/bin/env python3
"""
Goal Sender 노드 (웨이포인트 경유 버전)
- POI ID를 받으면 현재 위치 기준 경로 테이블 조회
- 경유지(center) + 목적지(방)를 navigate_through_poses로 한 번에 전송
- 경유지 yaw는 다음 지점 향하도록 atan2로 1회 계산
- 방 yaw는 destinations.yaml에 저장된 값(방문 보는 방향) 사용

위치 추적 (하이브리드):
  - 초기: 노드 시작 시 current_id = 'start'
  - 성공(SUCCEEDED): current_id = 목적지로 갱신
  - 실패(ABORTED): amcl_pose로 가장 가까운 POI 찾아 재동기화 후 멈춤(대기)

서비스/토픽:
  구독: /navigate_to_poi (std_msgs/String) - 목적지 id
        /cancel_navigation (std_msgs/String)
        /amcl_pose (PoseWithCovarianceStamped) - 재동기화용
  발행: /nav_state (std_msgs/String)
"""
import os
import math

import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from rclpy.callback_groups import ReentrantCallbackGroup
from nav2_msgs.action import NavigateThroughPoses
from geometry_msgs.msg import PoseStamped, PoseWithCovarianceStamped
from std_msgs.msg import String
import yaml


# 상태 상수
STATE_IDLE = 'IDLE'
STATE_NAVIGATING = 'NAVIGATING'
STATE_ARRIVED = 'ARRIVED'
STATE_ERROR = 'ERROR'
STATE_CANCELLED = 'CANCELLED'

# 시작점 좌표 (측정값) - 재동기화 시 'start' 위치 비교용
START_POSE = {'x': -0.022, 'y': 0.254}

# 경로 테이블: (현재위치, 목적지) → 거쳐갈 POI 리스트 (마지막이 목적지)
ROUTE_TABLE = {
    ('start', '301'): ['center1', '301'],
    ('start', '302'): ['center1', '302'],
    ('start', '303'): ['center2', '303'],
    ('301', '302'):   ['center1', '302'],
    ('301', '303'):   ['center1', 'center2', '303'],
    ('302', '303'):   ['center1', 'center2', '303'],
    ('302', '301'):   ['center1', '301'],
    ('303', '301'):   ['center2', 'center1', '301'],
    ('303', '302'):   ['center2', 'center1', '302'],
    # 같은 방향 복귀 등 누락 케이스는 fallback에서 직접 이동 처리
}


class GoalSender(Node):
    def __init__(self):
        super().__init__('goal_sender')

        self.cb_group = ReentrantCallbackGroup()

        self.declare_parameter('poi_file', os.path.expanduser(
            '~/hospital_robot_ws/src/hospital_robot_poi/poi/destinations.yaml'
        ))
        self.poi_file = self.get_parameter('poi_file').value

        self.destinations = self._load_poi()

        # 상태
        self.nav_state = STATE_IDLE
        self.current_id = 'start'          # ← 현재 위치 (POI id)
        self.current_goal_id = ''
        self.current_goal_name = ''
        self._goal_handle = None
        self._latest_amcl = None           # 최신 amcl_pose 저장 (재동기화용)

        # Nav2 액션 클라이언트 (NavigateThroughPoses)
        self.nav_client = ActionClient(
            self, NavigateThroughPoses, 'navigate_through_poses',
            callback_group=self.cb_group,
        )

        # 구독
        self.sub_goal = self.create_subscription(
            String, '/navigate_to_poi', self.goal_request_callback, 10,
        )
        self.sub_cancel = self.create_subscription(
            String, '/cancel_navigation', self.cancel_callback, 10,
        )
        # amcl_pose: 항상 최신값만 저장. 사용은 초기/실패 시에만.
        self.sub_amcl = self.create_subscription(
            PoseWithCovarianceStamped, '/amcl_pose', self.amcl_callback, 10,
        )

        # 상태 발행
        self.pub_state = self.create_publisher(String, '/nav_state', 10)
        self.state_timer = self.create_timer(0.5, self.publish_state)

        self.get_logger().info('=' * 50)
        self.get_logger().info('Goal Sender (웨이포인트 경유) 시작')
        self.get_logger().info(f'POI 파일: {self.poi_file}')
        self.get_logger().info(f'등록된 POI: {len(self.destinations)}개')
        self.get_logger().info(f'현재 위치: {self.current_id}')
        self.get_logger().info('사용법:')
        self.get_logger().info('  ros2 topic pub /navigate_to_poi std_msgs/String "data: 301" --once')
        self.get_logger().info('=' * 50)
        self._print_poi()

    # ---------- POI 로딩 ----------
    def _load_poi(self):
        if not os.path.exists(self.poi_file):
            self.get_logger().error(f'POI 파일 없음: {self.poi_file}')
            return {}
        with open(self.poi_file, 'r') as f:
            data = yaml.safe_load(f)
        if not data or 'destinations' not in data:
            self.get_logger().error('잘못된 POI 파일 형식')
            return {}
        poi_dict = {}
        for d in data['destinations']:
            poi_dict[d['id']] = d
        return poi_dict

    def _print_poi(self):
        if not self.destinations:
            return
        self.get_logger().info('── 등록된 목적지 ──')
        for poi_id, d in self.destinations.items():
            self.get_logger().info(
                f"  [{poi_id}] {d.get('name', poi_id)} "
                f"({d['x']:.2f}, {d['y']:.2f}) type={d.get('type', '?')}"
            )

    # ---------- amcl ----------
    def amcl_callback(self, msg: PoseWithCovarianceStamped):
        # 최신값만 저장. 평소엔 사용 안 함 (실패 시 재동기화 때만 읽음)
        self._latest_amcl = msg.pose.pose

    def _resync_from_amcl(self):
        """실패 시: amcl 위치로 가장 가까운 POI를 찾아 current_id 갱신"""
        if self._latest_amcl is None:
            self.get_logger().warn('재동기화 실패: amcl_pose 수신 이력 없음. 위치 유지.')
            return
        px = self._latest_amcl.position.x
        py = self._latest_amcl.position.y

        # 비교 대상: 모든 POI + start
        candidates = {'start': START_POSE}
        for pid, d in self.destinations.items():
            candidates[pid] = {'x': d['x'], 'y': d['y']}

        nearest_id = None
        nearest_dist = float('inf')
        for pid, p in candidates.items():
            dist = math.hypot(px - p['x'], py - p['y'])
            if dist < nearest_dist:
                nearest_dist = dist
                nearest_id = pid

        self.current_id = nearest_id
        self.get_logger().warn(
            f'🔄 재동기화: 현재 위치 ≈ [{nearest_id}] '
            f'(amcl {px:.2f},{py:.2f} / 거리 {nearest_dist:.2f}m)'
        )

    # ---------- 경로 생성 ----------
    def _build_path(self, target_id):
        """현재위치 → 목적지 경로(POI id 리스트) 반환"""
        key = (self.current_id, target_id)
        if key in ROUTE_TABLE:
            return ROUTE_TABLE[key]
        # fallback: 테이블에 없으면 직접 이동
        self.get_logger().warn(
            f'경로 테이블에 ({self.current_id}→{target_id}) 없음. 직접 이동.'
        )
        return [target_id]

    def _make_pose(self, x, y, yaw):
        ps = PoseStamped()
        ps.header.frame_id = 'map'
        ps.header.stamp = self.get_clock().now().to_msg()
        ps.pose.position.x = float(x)
        ps.pose.position.y = float(y)
        ps.pose.position.z = 0.0
        ps.pose.orientation.z = math.sin(yaw / 2.0)
        ps.pose.orientation.w = math.cos(yaw / 2.0)
        return ps

    def _build_poses(self, path):
        """경로 리스트 → PoseStamped 리스트 (경유지 yaw 자동계산)"""
        poses = []
        for i, pid in enumerate(path):
            poi = self.destinations[pid]
            ptype = poi.get('type', 'room')
            if ptype == 'waypoint' and i + 1 < len(path):
                # 경유지: 다음 지점 향하는 방향 (atan2 1회)
                nxt = self.destinations[path[i + 1]]
                yaw = math.atan2(nxt['y'] - poi['y'], nxt['x'] - poi['x'])
            else:
                # 방(목적지): 저장된 yaw (방문 보는 방향)
                yaw = float(poi.get('yaw', 0.0))
            poses.append(self._make_pose(poi['x'], poi['y'], yaw))
        return poses

    # ---------- 목적지 요청 ----------
    def goal_request_callback(self, msg: String):
        target_id = msg.data.strip()

        if target_id not in self.destinations:
            self.get_logger().error(f'❌ POI "{target_id}" 없음')
            self.nav_state = STATE_ERROR
            return

        if target_id == self.current_id:
            self.get_logger().info(f'이미 [{target_id}]에 있음. 이동 안 함.')
            return

        # 주행 중이면 기존 취소
        if self.nav_state == STATE_NAVIGATING and self._goal_handle is not None:
            self.get_logger().info('⚠️ 기존 목표 취소 후 새 목표로 전환')
            self._goal_handle.cancel_goal_async()

        path = self._build_path(target_id)
        poses = self._build_poses(path)

        self.current_goal_id = target_id
        self.current_goal_name = self.destinations[target_id].get('name', target_id)

        route_str = ' → '.join(path)
        self.get_logger().info(
            f'🚀 [{self.current_id}] → [{target_id}] 경로: {route_str}'
        )

        if not self.nav_client.wait_for_server(timeout_sec=5.0):
            self.get_logger().error('❌ Nav2(navigate_through_poses) 서버 연결 실패')
            self.nav_state = STATE_ERROR
            return

        goal_msg = NavigateThroughPoses.Goal()
        goal_msg.poses = poses

        self.nav_state = STATE_NAVIGATING
        send_future = self.nav_client.send_goal_async(
            goal_msg, feedback_callback=self.feedback_callback,
        )
        send_future.add_done_callback(self.goal_response_callback)

    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().error('❌ Nav2가 목표를 거절')
            self.nav_state = STATE_ERROR
            return
        self.get_logger().info('✅ Nav2 목표 수락')
        self._goal_handle = goal_handle
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self.result_callback)

    def feedback_callback(self, feedback_msg):
        fb = feedback_msg.feedback
        remaining = getattr(fb, 'distance_remaining', 0.0)
        poses_remaining = getattr(fb, 'number_of_poses_remaining', -1)
        self.get_logger().info(
            f'📍 이동중 → {self.current_goal_name} '
            f'(남은거리 {remaining:.2f}m, 남은경유점 {poses_remaining})',
            throttle_duration_sec=2.0,
        )

    def result_callback(self, future):
        status = future.result().status

        if status == 4:  # SUCCEEDED
            self.nav_state = STATE_ARRIVED
            self.current_id = self.current_goal_id   # ← 위치 갱신
            self.get_logger().info(
                f'🎉 도착! [{self.current_id}] {self.current_goal_name}'
            )
        elif status == 5:  # CANCELED
            self.nav_state = STATE_CANCELLED
            self.get_logger().info('⛔ 주행 취소됨 (위치 미갱신)')
            self._resync_from_amcl()   # 취소 시에도 현재 위치 재파악
        else:  # 6 ABORTED 등
            self.nav_state = STATE_ERROR
            self.get_logger().error(
                f'❌ 주행 실패 (status {status}). 정지 후 위치 재동기화.'
            )
            self._resync_from_amcl()   # ← 위치만 재동기화, 멈춤(자동 재출발 X)

        self._goal_handle = None

    def cancel_callback(self, msg: String):
        if self._goal_handle is not None:
            self.get_logger().info('⛔ 주행 취소 요청')
            self._goal_handle.cancel_goal_async()
        else:
            self.get_logger().info('취소할 목표 없음')

    def publish_state(self):
        m = String()
        m.data = (
            f'{{"state": "{self.nav_state}", '
            f'"current_id": "{self.current_id}", '
            f'"goal_id": "{self.current_goal_id}", '
            f'"goal_name": "{self.current_goal_name}"}}'
        )
        self.pub_state.publish(m)


def main(args=None):
    rclpy.init(args=args)
    node = GoalSender()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info('Goal Sender 종료')
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()