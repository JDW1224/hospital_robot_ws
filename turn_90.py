#!/usr/bin/env python3
"""
정확히 지정 각도만큼 제자리 회전하고 자동 정지 (시간 기반).
사용:
  python3 turn_90.py            # 기본 90도
  python3 turn_90.py 360        # 360도
  python3 turn_90.py 90 0.3     # 90도를 0.3rad/s로(더 천천히)
주의: 이건 "명령상" 각도. 실제 회전과 odom/imu 비교가 목적이므로
      바닥 표시/벽 모서리로 실제 90도인지 눈으로도 확인할 것.
"""
import sys, time, math
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist

class Turner(Node):
    def __init__(self, deg, wz):
        super().__init__('turner')
        self.pub = self.create_publisher(Twist, '/cmd_vel_hc', 10)
        self.wz = wz
        self.duration = math.radians(deg) / wz   # 회전에 필요한 시간
        self.deg = deg

    def run(self):
        # 퍼블리셔 연결 잠깐 대기
        time.sleep(0.5)
        t = Twist(); t.angular.z = self.wz
        start = time.time()
        rate_dt = 0.05
        self.get_logger().info(f'{self.deg}도 회전 시작 ({self.duration:.2f}초, {self.wz}rad/s)')
        while time.time() - start < self.duration:
            self.pub.publish(t)
            time.sleep(rate_dt)
        # 정지 명령 여러 번 (확실히)
        stop = Twist()
        for _ in range(10):
            self.pub.publish(stop)
            time.sleep(0.02)
        self.get_logger().info('정지 완료')

def main():
    deg = float(sys.argv[1]) if len(sys.argv) > 1 else 90.0
    wz  = float(sys.argv[2]) if len(sys.argv) > 2 else 0.5
    rclpy.init()
    n = Turner(deg, wz)
    try:
        n.run()
    finally:
        n.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
