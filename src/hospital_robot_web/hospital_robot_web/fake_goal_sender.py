#!/usr/bin/env python3
"""
가짜 goal_sender (테스트 전용 / 로봇 시뮬레이터)
- 실제 로봇/Nav2 없이 웹서버 전체 흐름을 테스트하기 위한 노드
- /navigate_to_poi (String) 수신 → "이동중" 흉내 → 몇 초 후 "도착" 발행
- /nav_state (String, JSON) 발행 → 웹서버가 받아 아이폰에 표시

⚠️ 발표/실제 주행엔 쓰지 않음. 진짜는 hospital_robot_navigation의 goal_sender.
   이건 노트북+휴대폰만으로 웹 UI를 검증하는 용도.

실행:
  ros2 run hospital_robot_web fake_goal_sender
  또는
  python3 fake_goal_sender.py
"""
import json
import threading
import time

import rclpy
from rclpy.node import Node
from std_msgs.msg import String


STATE_IDLE = 'IDLE'
STATE_NAVIGATING = 'NAVIGATING'
STATE_ARRIVED = 'ARRIVED'
STATE_CANCELLED = 'CANCELLED'


class FakeGoalSender(Node):
    def __init__(self):
        super().__init__('fake_goal_sender')

        self.state = STATE_IDLE
        self.goal_id = ''
        self.goal_name = ''
        self._nav_thread = None
        self._cancel_flag = False

        # 간단한 이름 매핑 (실제로는 goal_sender가 POI yaml에서 읽음)
        self.names = {
            '301': '301호',
            '302': '302호',
            'restroom': '화장실',
            'nurse_station': '간호사스테이션',
        }

        self.sub_goal = self.create_subscription(
            String, '/navigate_to_poi', self.on_goal, 10
        )
        self.sub_cancel = self.create_subscription(
            String, '/cancel_navigation', self.on_cancel, 10
        )
        self.pub_state = self.create_publisher(String, '/nav_state', 10)

        # 0.5초마다 상태 발행 (실제 goal_sender와 동일 주기)
        self.timer = self.create_timer(0.5, self.publish_state)

        self.get_logger().info('=' * 50)
        self.get_logger().info('🤖 가짜 goal_sender (테스트용) 시작')
        self.get_logger().info('   /navigate_to_poi 받으면 이동 흉내 → 도착')
        self.get_logger().info('   실제 로봇 없이 웹 UI 검증용')
        self.get_logger().info('=' * 50)

    def on_goal(self, msg: String):
        poi_id = msg.data.strip()
        name = self.names.get(poi_id, poi_id)

        self.get_logger().info(f'🚀 목적지 수신: [{poi_id}] {name}')

        # 기존 주행 취소
        self._cancel_flag = True
        if self._nav_thread and self._nav_thread.is_alive():
            self._nav_thread.join(timeout=1.0)

        self.goal_id = poi_id
        self.goal_name = name
        self._cancel_flag = False

        # 별도 스레드에서 이동 흉내 (3초 후 도착)
        self._nav_thread = threading.Thread(target=self._simulate_nav, daemon=True)
        self._nav_thread.start()

    def _simulate_nav(self):
        """이동 흉내: NAVIGATING 3초 → ARRIVED"""
        self.state = STATE_NAVIGATING
        self.get_logger().info(f'   → 이동 중... ({self.goal_name})')

        for _ in range(6):  # 3초 (0.5 × 6)
            if self._cancel_flag:
                self.get_logger().info('   → 취소됨')
                return
            time.sleep(0.5)

        self.state = STATE_ARRIVED
        self.get_logger().info(f'   🎉 도착! ({self.goal_name})')

        # 도착 3초 후 IDLE 복귀
        time.sleep(3.0)
        if self.state == STATE_ARRIVED:
            self.state = STATE_IDLE
            self.goal_id = ''
            self.goal_name = ''

    def on_cancel(self, msg: String):
        self.get_logger().info('🛑 취소 수신')
        self._cancel_flag = True
        self.state = STATE_CANCELLED
        self.goal_id = ''
        self.goal_name = ''

    def publish_state(self):
        m = String()
        m.data = json.dumps({
            'state': self.state,
            'goal_id': self.goal_id,
            'goal_name': self.goal_name,
        }, ensure_ascii=False)
        self.pub_state.publish(m)


def main(args=None):
    rclpy.init(args=args)
    node = FakeGoalSender()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
