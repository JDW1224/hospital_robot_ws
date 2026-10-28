#!/usr/bin/env python3
"""
Goal Sender 노드 (경유점 순차 도착 버전)
- POI ID를 받으면 현재 위치 기준 경로 테이블 조회
- 경로의 각 점(경유지/목적지)을 navigate_to_pose로 '하나씩 정확히 도착'하며 진행
- 경유지 yaw는 다음 지점 향하도록 atan2로 1회 계산
- 방 yaw는 destinations.yaml의 저장값(방문 보는 방향) 사용

위치 추적 (하이브리드):
  - 초기: current_id = 'start'
  - 각 구간 SUCCEEDED 시 그 점으로 current_id 갱신
  - 실패(ABORTED): 멈추고 amcl_pose로 재동기화 후 대기 (자동 재출발 X)

토픽:
  구독: /navigate_to_poi (std_msgs/String)
        /cancel_navigation (std_msgs/String)
        /amcl_pose (PoseWithCovarianceStamped)
  발행: /nav_state (std_msgs/String)
"""
import os
import math

import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from rclpy.callback_groups import ReentrantCallbackGroup
from nav2_msgs.action import NavigateToPose
from geometry_msgs.msg import PoseStamped, PoseWithCovarianceStamped, Twist
from std_msgs.msg import String, Bool
import yaml


STATE_IDLE = 'IDLE'
STATE_NAVIGATING = 'NAVIGATING'
STATE_ARRIVED = 'ARRIVED'
STATE_ERROR = 'ERROR'
STATE_CANCELLED = 'CANCELLED'
STATE_ESTOP = 'ESTOP'

START_POSE = {'x': -0.022, 'y': 0.254}

# 경유점 그래프 (무방향). 엣지 가중치 = 두 노드 좌표 유클리드 거리(런타임 계산).
#   301 ── center1 ── center2 ── 303
#                │
#               302
GRAPH_EDGES = {
    '301':     ['center1'],
    '302':     ['center1'],
    '303':     ['center2'],
    'center1': ['301', '302', 'center2'],
    'center2': ['303', 'center1'],
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
        self.current_id = 'start'
        self.current_goal_id = ''      # 최종 목적지
        self.current_goal_name = ''
        self._goal_handle = None
        self._latest_amcl = None

        # 비상정지
        self._estop = False            # True면 ESTOP 상태
        self._estop_saved_goal = None  # 비상정지 직전 목표(해제 시 자동 재출발용)

        # 순차 실행용
        self._segment_path = []        # 현재 경로 [center1, 301] 등
        self._segment_index = 0        # 지금 향하는 점의 인덱스

        self.nav_client = ActionClient(
            self, NavigateToPose, 'navigate_to_pose',
            callback_group=self.cb_group,
        )

        self.sub_goal = self.create_subscription(
            String, '/navigate_to_poi', self.goal_request_callback, 10)
        self.sub_cancel = self.create_subscription(
            String, '/cancel_navigation', self.cancel_callback, 10)
        self.sub_amcl = self.create_subscription(
            PoseWithCovarianceStamped, '/amcl_pose', self.amcl_callback, 10)
        self.sub_estop = self.create_subscription(
            Bool, '/emergency_stop', self.estop_callback, 10)

        # 비상정지 시 완전 정지용 (모터 구독 토픽 /cmd_vel_hc로 0 1회 발행)
        self.pub_stop = self.create_publisher(Twist, '/cmd_vel_hc', 10)

        self.pub_state = self.create_publisher(String, '/nav_state', 10)
        self.state_timer = self.create_timer(0.5, self.publish_state)

        self.get_logger().info('=' * 50)
        self.get_logger().info('Goal Sender (경유점 순차 도착) 시작')
        self.get_logger().info(f'등록된 POI: {len(self.destinations)}개')
        self.get_logger().info(f'현재 위치: {self.current_id}')
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
        return {d['id']: d for d in data['destinations']}

    def _print_poi(self):
        if not self.destinations:
            return
        self.get_logger().info('── 등록된 목적지 ──')
        for poi_id, d in self.destinations.items():
            self.get_logger().info(
                f"  [{poi_id}] {d.get('name', poi_id)} "
                f"({d['x']:.2f}, {d['y']:.2f}) type={d.get('type', '?')}")

    # ---------- amcl ----------
    def amcl_callback(self, msg: PoseWithCovarianceStamped):
        self._latest_amcl = msg.pose.pose

    def _resync_from_amcl(self):
        if self._latest_amcl is None:
            self.get_logger().warn('재동기화 실패: amcl_pose 이력 없음. 위치 유지.')
            return
        px = self._latest_amcl.position.x
        py = self._latest_amcl.position.y
        candidates = {'start': START_POSE}
        for pid, d in self.destinations.items():
            candidates[pid] = {'x': d['x'], 'y': d['y']}
        nearest_id, nearest_dist = None, float('inf')
        for pid, p in candidates.items():
            dist = math.hypot(px - p['x'], py - p['y'])
            if dist < nearest_dist:
                nearest_dist, nearest_id = dist, pid
        self.current_id = nearest_id
        self.get_logger().warn(
            f'🔄 재동기화: 현재 위치 ≈ [{nearest_id}] '
            f'(amcl {px:.2f},{py:.2f} / {nearest_dist:.2f}m)')

    # ---------- 경로 (그래프 최단경로) ----------
    def _node_xy(self, node_id):
        """노드의 좌표. 'start'는 START_POSE, 나머지는 destinations."""
        if node_id == 'start':
            return START_POSE['x'], START_POSE['y']
        d = self.destinations[node_id]
        return d['x'], d['y']

    def _edge_cost(self, a, b):
        ax, ay = self._node_xy(a)
        bx, by = self._node_xy(b)
        return math.hypot(ax - bx, ay - by)

    def _shortest_path(self, start_node, target_id):
        """GRAPH_EDGES 위에서 start_node→target_id 최단경로(노드 리스트, start_node 포함).
        경로 없으면 [target_id] 폴백."""
        if start_node == target_id:
            return [target_id]
        if start_node not in GRAPH_EDGES or target_id not in GRAPH_EDGES:
            return [target_id]
        # 다익스트라 (노드 5개라 매우 가벼움)
        import heapq
        dist = {start_node: 0.0}
        prev = {}
        pq = [(0.0, start_node)]
        visited = set()
        while pq:
            d, u = heapq.heappop(pq)
            if u in visited:
                continue
            visited.add(u)
            if u == target_id:
                break
            for v in GRAPH_EDGES.get(u, []):
                nd = d + self._edge_cost(u, v)
                if v not in dist or nd < dist[v]:
                    dist[v] = nd
                    prev[v] = u
                    heapq.heappush(pq, (nd, v))
        if target_id not in prev and target_id != start_node:
            return [target_id]
        # 경로 복원
        path = [target_id]
        while path[-1] != start_node:
            path.append(prev[path[-1]])
        path.reverse()
        return path

    def _path_cost(self, node_list):
        """노드 리스트의 총 그래프 거리."""
        total = 0.0
        for i in range(len(node_list) - 1):
            total += self._edge_cost(node_list[i], node_list[i + 1])
        return total

    def _build_path(self, target_id):
        """현재 상태(self.current_id)에서 target_id까지 그래프 최단경로.
        current_id가 'start'면, 목표 쪽 그래프에 맞는 진입점 사용
        (목표가 그래프상 가장 가까운 노드부터 start를 잇는 셈).
        301/302→center1 진입, 303→center2 진입이 자연스럽게 나옴."""
        start_node = self.current_id
        if start_node == 'start':
            # start를 그래프에 임시 노드로 넣어, 양쪽 center 경유 중 총거리 짧은 쪽 선택
            via1 = ['center1'] + self._shortest_path('center1', target_id)[1:] \
                if 'center1' != target_id else ['center1']
            via2 = ['center2'] + self._shortest_path('center2', target_id)[1:] \
                if 'center2' != target_id else ['center2']
            cost1 = self._edge_cost('start', 'center1') + self._path_cost(via1)
            cost2 = self._edge_cost('start', 'center2') + self._path_cost(via2)
            return via1 if cost1 <= cost2 else via2
        return self._shortest_path(start_node, target_id)

    def _build_path_reroute(self, target_id):
        """주행 중 재지정 전용 경로 생성.
        현재 위치(AMCL 좌표)에서 갈 수 있는 모든 '진입 경유점' 후보의
        실제 총거리(현재→진입점 직선 + 진입점→목표 그래프최단)를 비교해 최소 선택.
        노드 고정이 아니라 연속 위치에서 재므로 불필요한 되돌아감을 방지한다.

        후보 진입점: 향하던 next, 떠난 prev, 그리고 두 center(c1,c2).
        (출발 직후처럼 prev가 'start'여도, center 직접 후보가 있어 올바르게 꺾인다)

        반환: 경로 노드 리스트. 판정 불가 시 None."""
        if not self._segment_path or self._latest_amcl is None:
            return None

        idx = self._segment_index
        path = self._segment_path
        next_node = path[idx] if idx < len(path) else None
        prev_node = path[idx - 1] if idx >= 1 else None
        if next_node is None:
            return None

        px = self._latest_amcl.position.x
        py = self._latest_amcl.position.y

        def cur_dist(node):
            if node in self.destinations:
                nx, ny = self.destinations[node]['x'], self.destinations[node]['y']
            else:
                return float('inf')
            return math.hypot(px - nx, py - ny)

        # 진입점 후보: 향하던 next + 떠난 prev + 두 center (중복 제거, 그래프 노드만)
        entries = set()
        for n in (next_node, prev_node, 'center1', 'center2'):
            if n in GRAPH_EDGES:
                entries.add(n)

        best_path, best_cost, best_entry = None, float('inf'), None
        for entry in entries:
            sub = [entry] if entry == target_id else self._shortest_path(entry, target_id)
            total = cur_dist(entry) + self._path_cost(sub)
            if total < best_cost:
                best_cost, best_path, best_entry = total, sub, entry

        if best_path is None:
            return None
        self.get_logger().info(
            f'🔀 재라우팅: 현재 위치에서 진입점 [{best_entry}] 선택 '
            f'({best_cost:.2f}m) → {" → ".join(best_path)}')
        return best_path

    def _make_goal(self, poi_id, next_id):
        """poi_id로 가는 NavigateToPose.Goal 생성. next_id가 있으면 경유지 yaw 계산."""
        poi = self.destinations[poi_id]
        ptype = poi.get('type', 'room')

        if ptype == 'waypoint' and next_id is not None:
            nxt = self.destinations[next_id]
            yaw = math.atan2(nxt['y'] - poi['y'], nxt['x'] - poi['x'])
        else:
            yaw = float(poi.get('yaw', 0.0))

        goal = NavigateToPose.Goal()
        ps = PoseStamped()
        ps.header.frame_id = 'map'
        ps.header.stamp = self.get_clock().now().to_msg()
        ps.pose.position.x = float(poi['x'])
        ps.pose.position.y = float(poi['y'])
        ps.pose.position.z = 0.0
        ps.pose.orientation.z = math.sin(yaw / 2.0)
        ps.pose.orientation.w = math.cos(yaw / 2.0)
        goal.pose = ps
        return goal

    # ---------- 목적지 요청 ----------
    def goal_request_callback(self, msg: String):
        target_id = msg.data.strip()

        # 비상정지 중에는 모든 목적지 명령 무시
        if self._estop:
            self.get_logger().warn('🛑 비상정지 상태 — 목적지 명령 무시 (해제 후 가능)')
            return

        if target_id not in self.destinations:
            self.get_logger().error(f'❌ POI "{target_id}" 없음')
            self.nav_state = STATE_ERROR
            return
        if target_id == self.current_id:
            self.get_logger().info(f'이미 [{target_id}]에 있음.')
            return

        # 주행 중이면 기존 취소 + 양방향 재라우팅
        rerouted = None
        if self.nav_state == STATE_NAVIGATING and self._goal_handle is not None:
            self.get_logger().info('⚠️ 기존 목표 취소 후 새 목표 (재지정)')
            self._goal_handle.cancel_goal_async()
            rerouted = self._build_path_reroute(target_id)

        if rerouted is not None:
            self._segment_path = rerouted
        else:
            self._segment_path = self._build_path(target_id)
        self._segment_index = 0
        self.current_goal_id = target_id
        self.current_goal_name = self.destinations[target_id].get('name', target_id)

        self.get_logger().info(
            f'🚀 [{self.current_id}] → [{target_id}] 경로: '
            f'{" → ".join(self._segment_path)}')

        if not self.nav_client.wait_for_server(timeout_sec=5.0):
            self.get_logger().error('❌ Nav2 서버 연결 실패')
            self.nav_state = STATE_ERROR
            return

        self.nav_state = STATE_NAVIGATING
        self._send_next_segment()

    def _send_next_segment(self):
        """경로의 현재 인덱스 점으로 navigate_to_pose 전송"""
        idx = self._segment_index
        path = self._segment_path
        poi_id = path[idx]
        next_id = path[idx + 1] if idx + 1 < len(path) else None

        goal = self._make_goal(poi_id, next_id)

        seg_kind = '경유지' if next_id is not None and \
            self.destinations[poi_id].get('type') == 'waypoint' else '목적지'
        self.get_logger().info(
            f'  ▶ 구간 {idx + 1}/{len(path)}: [{poi_id}] ({seg_kind})로 이동')

        send_future = self.nav_client.send_goal_async(
            goal, feedback_callback=self.feedback_callback)
        send_future.add_done_callback(self.goal_response_callback)

    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().error('❌ Nav2가 목표 거절')
            self.nav_state = STATE_ERROR
            return
        self._goal_handle = goal_handle
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self.result_callback)

    def feedback_callback(self, feedback_msg):
        fb = feedback_msg.feedback
        remaining = getattr(fb, 'distance_remaining', 0.0)
        cur_target = self._segment_path[self._segment_index]
        self.get_logger().info(
            f'📍 [{cur_target}] 이동중 (남은거리 {remaining:.2f}m)',
            throttle_duration_sec=2.0)

    def result_callback(self, future):
        status = future.result().status
        self._goal_handle = None

        if status == 4:  # SUCCEEDED
            arrived_id = self._segment_path[self._segment_index]
            self.current_id = arrived_id          # 구간 도착 → 위치 갱신
            self.get_logger().info(f'  ✅ [{arrived_id}] 도착')

            # 다음 구간 있으면 진행
            if self._segment_index + 1 < len(self._segment_path):
                self._segment_index += 1
                self._send_next_segment()
            else:
                # 최종 목적지 도착
                self.nav_state = STATE_ARRIVED
                self.get_logger().info(
                    f'🎉 최종 도착! [{self.current_id}] {self.current_goal_name}')

        elif status == 5:  # CANCELED
            self.nav_state = STATE_CANCELLED
            self.get_logger().info('⛔ 주행 취소됨')
            self._resync_from_amcl()
        else:  # ABORTED 등
            self.nav_state = STATE_ERROR
            self.get_logger().error(
                f'❌ 주행 실패 (status {status}). 정지 후 재동기화.')
            self._resync_from_amcl()

    def cancel_callback(self, msg: String):
        if self._goal_handle is not None:
            self.get_logger().info('⛔ 주행 취소 요청')
            self._goal_handle.cancel_goal_async()
        else:
            self.get_logger().info('취소할 목표 없음')

    def estop_callback(self, msg: Bool):
        """비상정지 토글. True=비상정지 진입, False=해제."""
        want_estop = bool(msg.data)

        if want_estop and not self._estop:
            # ── 비상정지 진입 ──
            self._estop = True
            # 해제 후 자동 재출발을 위해 직전 목표 저장 (주행 중이었다면)
            if self.nav_state == STATE_NAVIGATING and self.current_goal_id:
                self._estop_saved_goal = self.current_goal_id
            else:
                self._estop_saved_goal = None
            # 1) nav2 목표 취소
            if self._goal_handle is not None:
                self._goal_handle.cancel_goal_async()
            # 2) 완전 정지: 0 속도 1회 발행 (잔여 명령/관성 차단)
            self.pub_stop.publish(Twist())
            self.nav_state = STATE_ESTOP
            self.get_logger().warn('🛑 비상정지! 목표 취소 + 정지. (해제 전까지 명령 무시)')

        elif not want_estop and self._estop:
            # ── 비상정지 해제 ──
            self._estop = False
            self.get_logger().info('✅ 비상정지 해제')
            saved = self._estop_saved_goal
            self._estop_saved_goal = None
            if saved and saved in self.destinations:
                # 멈추기 전 목표로 현재 위치부터 재라우팅하여 자동 재출발
                self.get_logger().info(f'  ↻ [{saved}]로 자동 재출발')
                self._resync_from_amcl()  # 현재 위치 갱신
                self._restart_to(saved)
            else:
                self.nav_state = STATE_IDLE

    def _restart_to(self, target_id):
        """현재 위치에서 target_id로 경로 만들어 주행 시작 (해제 후 재출발용)."""
        # 정지 상태에서 재출발하므로 current_id 기준 그래프 경로
        self._segment_path = self._build_path(target_id)
        self._segment_index = 0
        self.current_goal_id = target_id
        self.current_goal_name = self.destinations[target_id].get('name', target_id)
        if not self.nav_client.wait_for_server(timeout_sec=5.0):
            self.get_logger().error('❌ Nav2 서버 연결 실패')
            self.nav_state = STATE_ERROR
            return
        self.get_logger().info(
            f'🚀 [{self.current_id}] → [{target_id}] 경로: '
            f'{" → ".join(self._segment_path)}')
        self.nav_state = STATE_NAVIGATING
        self._send_next_segment()

    def publish_state(self):
        m = String()
        cur_seg = ''
        if self.nav_state == STATE_NAVIGATING and self._segment_path:
            cur_seg = self._segment_path[self._segment_index]
        m.data = (
            f'{{"state": "{self.nav_state}", '
            f'"current_id": "{self.current_id}", '
            f'"goal_id": "{self.current_goal_id}", '
            f'"goal_name": "{self.current_goal_name}", '
            f'"segment": "{cur_seg}"}}')
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