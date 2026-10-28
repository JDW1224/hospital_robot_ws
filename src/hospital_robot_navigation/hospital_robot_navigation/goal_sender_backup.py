#!/usr/bin/env python3
"""
Goal Sender 노드
- POI ID를 받으면 destinations.yaml에서 좌표 조회
- Nav2 NavigateToPose 액션으로 전송
- 결과 피드백 (성공/실패/진행률)

서비스:
  /navigate_to_poi (hospital_robot_msgs/srv/SetDestination)
    - destination_id: str → success: bool, message: str

토픽 발행:
  /robot_status (hospital_robot_msgs/msg/RobotStatus)
    - nav_state, current_goal, progress 등
"""
import os
import math

import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from rclpy.callback_groups import ReentrantCallbackGroup
from nav2_msgs.action import NavigateToPose
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import String
import yaml


# 상태 상수
STATE_IDLE = 'IDLE'
STATE_NAVIGATING = 'NAVIGATING'
STATE_ARRIVED = 'ARRIVED'
STATE_ERROR = 'ERROR'
STATE_CANCELLED = 'CANCELLED'


class GoalSender(Node):
    def __init__(self):
        super().__init__('goal_sender')

        self.cb_group = ReentrantCallbackGroup()

        # 파라미터
        self.declare_parameter('poi_file', os.path.expanduser(
            '~/hospital_robot_ws/src/hospital_robot_poi/poi/destinations.yaml'
        ))
        # use_sim_time is auto-declared

        self.poi_file = self.get_parameter('poi_file').value

        # POI 데이터 로드
        self.destinations = self._load_poi()

        # 상태
        self.nav_state = STATE_IDLE
        self.current_goal_id = ''
        self.current_goal_name = ''
        self._goal_handle = None

        # Nav2 액션 클라이언트
        self.nav_client = ActionClient(
            self, NavigateToPose, 'navigate_to_pose',
            callback_group=self.cb_group,
        )

        # 목적지 요청 구독 (간단한 String 토픽)
        self.sub_goal = self.create_subscription(
            String, '/navigate_to_poi', self.goal_request_callback, 10,
        )

        # 취소 요청 구독
        self.sub_cancel = self.create_subscription(
            String, '/cancel_navigation', self.cancel_callback, 10,
        )

        # 상태 발행
        self.pub_state = self.create_publisher(String, '/nav_state', 10)
        self.state_timer = self.create_timer(0.5, self.publish_state)

        self.get_logger().info('='*50)
        self.get_logger().info('Goal Sender 시작')
        self.get_logger().info(f'POI 파일: {self.poi_file}')
        self.get_logger().info(f'등록된 POI: {len(self.destinations)}개')
        self.get_logger().info('')
        self.get_logger().info('사용법:')
        self.get_logger().info('  ros2 topic pub /navigate_to_poi std_msgs/String "data: 301" --once')
        self.get_logger().info('  ros2 topic pub /cancel_navigation std_msgs/String "data: cancel" --once')
        self.get_logger().info('='*50)
        self._print_poi()

    def _load_poi(self):
        """destinations.yaml 로드"""
        if not os.path.exists(self.poi_file):
            self.get_logger().error(f'POI 파일 없음: {self.poi_file}')
            return {}

        with open(self.poi_file, 'r') as f:
            data = yaml.safe_load(f)

        if not data or 'destinations' not in data:
            self.get_logger().error('잘못된 POI 파일 형식')
            return {}

        # dict로 변환 (id → data)
        poi_dict = {}
        for d in data['destinations']:
            poi_dict[d['id']] = d
        return poi_dict

    def _print_poi(self):
        """POI 목록 출력"""
        if self.destinations:
            self.get_logger().info('── 등록된 목적지 ──')
            for poi_id, d in self.destinations.items():
                self.get_logger().info(
                    f"  [{poi_id}] {d.get('name', poi_id)} → "
                    f"({d['x']:.2f}, {d['y']:.2f})"
                )
            self.get_logger().info('')

    def goal_request_callback(self, msg: String):
        """목적지 요청 수신"""
        poi_id = msg.data.strip()

        # POI 조회
        poi = self.destinations.get(poi_id)
        if poi is None:
            self.get_logger().error(f'❌ POI "{poi_id}" 없음')
            self.nav_state = STATE_ERROR
            return

        # 이미 주행 중이면 취소 후 새 목표
        if self.nav_state == STATE_NAVIGATING and self._goal_handle is not None:
            self.get_logger().info(f'⚠️ 기존 목표 취소 후 새 목표로 전환')
            self._goal_handle.cancel_goal_async()

        self.current_goal_id = poi_id
        self.current_goal_name = poi.get('name', poi_id)

        # goal_pose 생성
        goal_msg = NavigateToPose.Goal()
        goal_msg.pose = PoseStamped()
        goal_msg.pose.header.frame_id = 'map'
        goal_msg.pose.header.stamp = self.get_clock().now().to_msg()
        goal_msg.pose.pose.position.x = float(poi['x'])
        goal_msg.pose.pose.position.y = float(poi['y'])
        goal_msg.pose.pose.position.z = 0.0

        # yaw → quaternion
        yaw = float(poi.get('yaw', 0.0))
        goal_msg.pose.pose.orientation.z = math.sin(yaw / 2.0)
        goal_msg.pose.pose.orientation.w = math.cos(yaw / 2.0)

        self.get_logger().info(
            f'🚀 목적지: [{poi_id}] {self.current_goal_name} '
            f'({poi["x"]:.2f}, {poi["y"]:.2f})'
        )

        # Nav2 서버 대기
        if not self.nav_client.wait_for_server(timeout_sec=5.0):
            self.get_logger().error('❌ Nav2 서버 연결 실패')
            self.nav_state = STATE_ERROR
            return

        # 액션 전송
        self.nav_state = STATE_NAVIGATING
        send_goal_future = self.nav_client.send_goal_async(
            goal_msg,
            feedback_callback=self.feedback_callback,
        )
        send_goal_future.add_done_callback(self.goal_response_callback)

    def goal_response_callback(self, future):
        """Nav2 goal 수락/거절 응답"""
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().error('❌ Nav2가 목표를 거절했습니다')
            self.nav_state = STATE_ERROR
            return

        self.get_logger().info('✅ Nav2가 목표를 수락했습니다')
        self._goal_handle = goal_handle

        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self.result_callback)

    def feedback_callback(self, feedback_msg):
        """Nav2 진행 피드백"""
        feedback = feedback_msg.feedback
        current = feedback.current_pose.pose.position
        remaining = feedback.distance_remaining

        self.get_logger().info(
            f'📍 이동중 → {self.current_goal_name} '
            f'(현재: {current.x:.1f}, {current.y:.1f} | '
            f'남은거리: {remaining:.2f}m)',
            throttle_duration_sec=2.0,
        )

    def result_callback(self, future):
        """Nav2 최종 결과"""
        result = future.result()
        status = result.status

        if status == 4:  # SUCCEEDED
            self.nav_state = STATE_ARRIVED
            self.get_logger().info(
                f'🎉 도착! [{self.current_goal_id}] {self.current_goal_name}'
            )
        elif status == 5:  # CANCELED
            self.nav_state = STATE_CANCELLED
            self.get_logger().info('⛔ 주행 취소됨')
        else:
            self.nav_state = STATE_ERROR
            self.get_logger().error(f'❌ 주행 실패 (status: {status})')

        self._goal_handle = None

    def cancel_callback(self, msg: String):
        """주행 취소 요청"""
        if self._goal_handle is not None:
            self.get_logger().info('⛔ 주행 취소 요청')
            self._goal_handle.cancel_goal_async()
        else:
            self.get_logger().info('취소할 목표 없음')

    def publish_state(self):
        """상태 발행"""
        state_msg = String()
        state_msg.data = (
            f'{{"state": "{self.nav_state}", '
            f'"goal_id": "{self.current_goal_id}", '
            f'"goal_name": "{self.current_goal_name}"}}'
        )
        self.pub_state.publish(state_msg)


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
