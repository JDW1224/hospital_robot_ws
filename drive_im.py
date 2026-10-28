#!/usr/bin/env python3
"""
1m 직진 자동 정지 노드 (오도메트리 기반)
- 시작 시 현재 위치 기록
- /cmd_vel_hc로 직진 명령
- 오도메트리 기반 이동 거리가 1m 도달하면 정지
- 결과 출력

사용:
    python3 drive_1m.py
    또는
    python3 drive_1m.py --distance 1.0 --speed 0.1
"""
import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Twist
import math
import argparse
import sys


class Drive1m(Node):
    def __init__(self, target_distance=1.0, speed=0.1):
        super().__init__('drive_1m')
        
        self.target_distance = target_distance   # 목표 거리 (m)
        self.speed = speed                        # 직진 속도 (m/s)
        
        # 상태
        self.start_x = None
        self.start_y = None
        self.current_x = 0.0
        self.current_y = 0.0
        self.distance_traveled = 0.0
        self.is_moving = False
        self.is_done = False
        
        # 구독자
        self.odom_sub = self.create_subscription(
            Odometry, '/odom', self.odom_callback, 10
        )
        
        # 발행자
        self.cmd_pub = self.create_publisher(Twist, '/cmd_vel_hc', 10)
        
        # 제어 타이머 (10Hz)
        self.timer = self.create_timer(0.1, self.control_loop)
        
        self.get_logger().info('=' * 50)
        self.get_logger().info(f'1m 직진 캘리브레이션 노드 시작')
        self.get_logger().info(f'목표 거리: {target_distance}m')
        self.get_logger().info(f'속도: {speed}m/s')
        self.get_logger().info('오도메트리 수신 대기 중...')
        self.get_logger().info('=' * 50)
    
    def odom_callback(self, msg):
        """오도메트리 수신"""
        self.current_x = msg.pose.pose.position.x
        self.current_y = msg.pose.pose.position.y
        
        # 시작 위치 설정 (첫 메시지)
        if self.start_x is None:
            self.start_x = self.current_x
            self.start_y = self.current_y
            self.is_moving = True
            self.get_logger().info(
                f'시작 위치 기록: x={self.start_x:.4f}, y={self.start_y:.4f}'
            )
            self.get_logger().info('직진 시작!')
        
        # 이동 거리 계산
        dx = self.current_x - self.start_x
        dy = self.current_y - self.start_y
        self.distance_traveled = math.sqrt(dx*dx + dy*dy)
    
    def control_loop(self):
        """제어 루프 - 10Hz"""
        if self.start_x is None:
            return
        
        if self.is_done:
            return
        
        # 진행 상황 출력 (10cm마다)
        progress = self.distance_traveled / self.target_distance * 100
        self.get_logger().info(
            f'진행: {self.distance_traveled:.3f}m / {self.target_distance}m ({progress:.1f}%)'
        )
        
        # 목표 도달 시 정지
        if self.distance_traveled >= self.target_distance:
            self.stop_robot()
            return
        
        # 직진 명령 발행
        cmd = Twist()
        cmd.linear.x = -self.speed
        cmd.angular.z = 0.0
        self.cmd_pub.publish(cmd)
    
    def stop_robot(self):
        """로봇 정지 및 결과 출력"""
        # 정지 명령 (10번 발행해서 확실하게)
        for _ in range(10):
            stop_cmd = Twist()
            self.cmd_pub.publish(stop_cmd)
        
        self.is_done = True
        self.is_moving = False
        
        # 결과 출력
        actual_dx = self.current_x - self.start_x
        actual_dy = self.current_y - self.start_y
        
        self.get_logger().info('=' * 50)
        self.get_logger().info('🎯 캘리브레이션 완료!')
        self.get_logger().info('=' * 50)
        self.get_logger().info(f'시작 위치: x={self.start_x:.4f}, y={self.start_y:.4f}')
        self.get_logger().info(f'종료 위치: x={self.current_x:.4f}, y={self.current_y:.4f}')
        self.get_logger().info(f'이동 거리 (x축):    {actual_dx:.4f}m')
        self.get_logger().info(f'이동 거리 (y축):    {actual_dy:.4f}m')
        self.get_logger().info(f'총 이동 거리:      {self.distance_traveled:.4f}m')
        self.get_logger().info(f'목표 거리:         {self.target_distance}m')
        self.get_logger().info('=' * 50)
        self.get_logger().info('👉 줄자로 실제 이동한 거리를 측정하세요!')
        self.get_logger().info('   실측값 / 오도메트리값 = 보정 계수')
        self.get_logger().info('=' * 50)


def main(args=None):
    parser = argparse.ArgumentParser(description='1m 직진 캘리브레이션')
    parser.add_argument('--distance', type=float, default=1.0, help='목표 거리 (m)')
    parser.add_argument('--speed', type=float, default=0.1, help='속도 (m/s)')
    parsed_args, remaining = parser.parse_known_args()
    
    rclpy.init(args=remaining)
    
    node = Drive1m(
        target_distance=parsed_args.distance,
        speed=parsed_args.speed
    )
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info('사용자 중단')
        node.stop_robot()
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()

