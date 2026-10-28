#!/usr/bin/env python3
"""
safety_gate 노드 (라이다 전방 비상정지 포함) - 휠체어 안전 최우선

흐름:
  Nav2 --(/cmd_vel_nav)--> [safety_gate] --(/cmd_vel)--> 바퀴(OpenCR)
                               ↑  ↑
        /perception/human_detected(Bool)   /scan(LaserScan)

정지 조건 (OR):
  1) 사람 감지(/perception/human_detected = true)  ← YOLO
  2) 전방 ±front_angle_deg 안에 라이다 최소거리 < stop_distance  ← 벽/장애물 ★이번 추가
둘 중 하나라도 걸리면 cmd_vel을 감속도 제한으로 0까지 부드럽게 정지.
조건 풀리고 clear_hold_sec 지나면 부드럽게 재출발.

★ 이게 핵심: 경로/추종이 완벽하지 않아도, 충돌 직전 물리적으로 정지시킴.
   통로 여유(cm)와 무관하게 안전 보장.

전제: Nav2 controller_server cmd_vel 출력을 /cmd_vel_nav 로 remap.
실행: ros2 run hospital_robot_perception safety_gate
"""
import math

import rclpy
from rclpy.node import Node
from std_msgs.msg import Bool
from geometry_msgs.msg import Twist
from sensor_msgs.msg import LaserScan


class SafetyGateNode(Node):
    def __init__(self):
        super().__init__('safety_gate_node')

        # ── 램프/히스테리시스 ──
        self.declare_parameter('control_hz', 20.0)
        self.declare_parameter('max_accel', 0.4)
        self.declare_parameter('max_decel', 0.5)
        self.declare_parameter('max_ang_accel', 1.0)
        self.declare_parameter('max_ang_decel', 1.5)
        self.declare_parameter('clear_hold_sec', 1.5)
        self.declare_parameter('cmd_timeout_sec', 0.5)
        self.declare_parameter('in_topic', '/cmd_vel_nav')
        self.declare_parameter('out_topic', '/cmd_vel')

        # ── 라이다 전방 비상정지 ──
        self.declare_parameter('use_lidar_stop', True)
        self.declare_parameter('scan_topic', '/scan')
        self.declare_parameter('stop_distance', 0.15)     # 정면 15cm
        self.declare_parameter('front_angle_deg', 50.0)
        self.declare_parameter('omni_stop', False)        # 정면 콘만(뒤는 라이다 사각지대라 의미없음)
        self.declare_parameter('robot_radius', 0.16)      # 임계 기준(통로24cm보다 작게)
        self.declare_parameter('side_margin', 0.03)       # → 임계 0.19m
        self.declare_parameter('forward_offset_deg', 180.0)  # 라이다0도→로봇전방 오프셋(180도 장착)
        self.declare_parameter('min_valid_range', 0.06)   # 이보다 작은 값은 노이즈로 무시
        self.declare_parameter('min_points', 2)           # 임계 미만 점이 N개 이상이어야 정지(단발 노이즈 방지)

        gp = self.get_parameter
        self.hz = float(gp('control_hz').value)
        self.max_accel = float(gp('max_accel').value)
        self.max_decel = float(gp('max_decel').value)
        self.max_ang_accel = float(gp('max_ang_accel').value)
        self.max_ang_decel = float(gp('max_ang_decel').value)
        self.clear_hold = float(gp('clear_hold_sec').value)
        self.cmd_timeout = float(gp('cmd_timeout_sec').value)
        in_topic = gp('in_topic').value
        out_topic = gp('out_topic').value
        self.use_lidar = bool(gp('use_lidar_stop').value)
        scan_topic = gp('scan_topic').value
        self.stop_distance = float(gp('stop_distance').value)
        self.front_angle = math.radians(float(gp('front_angle_deg').value))
        self.forward_offset = math.radians(float(gp('forward_offset_deg').value))
        self.omni_stop = bool(gp('omni_stop').value)
        self.robot_radius = float(gp('robot_radius').value)
        self.side_margin = float(gp('side_margin').value)
        self.min_valid = float(gp('min_valid_range').value)
        self.min_points = int(gp('min_points').value)

        # ── 상태 ──
        self.nav_v = 0.0
        self.nav_w = 0.0
        self.last_cmd_t = -1e9
        self.out_v = 0.0
        self.out_w = 0.0
        self.human_now = False
        self.last_block_t = -1e9     # 마지막으로 "정지조건 충족"한 시각
        self.lidar_block = False
        self.last_min_dist = float('inf')

        # ── 통신 ──
        self.create_subscription(Twist, in_topic, self.on_cmd, 10)
        self.create_subscription(Bool, '/perception/human_detected', self.on_human, 10)
        if self.use_lidar:
            self.create_subscription(LaserScan, scan_topic, self.on_scan, 5)
        self.pub_cmd = self.create_publisher(Twist, out_topic, 10)
        # 디버그: 현재 정지중인지 + 전방최소거리
        self.pub_stop = self.create_publisher(Bool, '/safety_gate/stopped', 10)

        self.create_timer(1.0 / self.hz, self.on_tick)
        self.get_logger().info(
            f'safety_gate: {in_topic}->{out_topic} | lidar_stop={self.use_lidar} '
            f'(<{self.stop_distance}m, ±{math.degrees(self.front_angle):.0f}deg)')

    def on_cmd(self, msg):
        self.nav_v = msg.linear.x
        self.nav_w = msg.angular.z
        self.last_cmd_t = self._now()

    def on_human(self, msg):
        self.human_now = bool(msg.data)
        if self.human_now:
            self.last_block_t = self._now()

    def on_scan(self, msg: LaserScan):
        """전방 ±front_angle 범위에서 임계거리 미만 점 개수를 셈."""
        n = len(msg.ranges)
        if n == 0:
            return
        close_count = 0
        min_d = float('inf')
        a = msg.angle_min
        inc = msg.angle_increment
        # omni 모드: 차체 외곽(robot_radius)에서 side_margin 안에 점 있으면 정지(전방위)
        thresh = (self.robot_radius + self.side_margin) if self.omni_stop else self.stop_distance
        for i in range(n):
            r = msg.ranges[i]
            if r != r:          # NaN
                continue
            if r < self.min_valid:
                continue
            if not self.omni_stop:
                ang = a + i * inc
                d = ang - self.forward_offset
                while d > math.pi:
                    d -= 2 * math.pi
                while d < -math.pi:
                    d += 2 * math.pi
                if not (-self.front_angle <= d <= self.front_angle):
                    continue
            if r < min_d:
                min_d = r
            if r < thresh:
                close_count += 1
        self.last_min_dist = min_d
        self.lidar_block = close_count >= self.min_points
        if not hasattr(self, '_scan_n'):
            self._scan_n = 0
        self._scan_n += 1
        if self.lidar_block:
            self.last_block_t = self._now()

    def on_tick(self):
        now = self._now()
        dt = 1.0 / self.hz

        blocking_now = self.human_now or self.lidar_block
        # 히스테리시스: 막힌 직후 clear_hold 동안 정지 유지
        stop_active = blocking_now or (now - self.last_block_t) < self.clear_hold
        cmd_fresh = (now - self.last_cmd_t) <= self.cmd_timeout

        if stop_active or not cmd_fresh:
            tv, tw = 0.0, 0.0
        else:
            tv, tw = self.nav_v, self.nav_w

        self.out_v = self._ramp(self.out_v, tv, self.max_accel * dt, self.max_decel * dt)
        self.out_w = self._ramp(self.out_w, tw, self.max_ang_accel * dt, self.max_ang_decel * dt)

        out = Twist()
        out.linear.x = self.out_v
        out.angular.z = self.out_w
        self.pub_cmd.publish(out)

        sm = Bool(); sm.data = bool(stop_active); self.pub_stop.publish(sm)

        # 디버그: 1초에 한 번 전방 최소거리/상태 출력
        if not hasattr(self, '_dbg_t'):
            self._dbg_t = 0.0
        if now - self._dbg_t > 1.0:
            self._dbg_t = now
            self.get_logger().info(
                f'front_min={self.last_min_dist:.2f}m lidar_block={self.lidar_block} '
                f'human={self.human_now} stop={stop_active} out_v={self.out_v:.2f}')

    @staticmethod
    def _ramp(cur, target, accel_step, decel_step):
        if target == cur:
            return cur
        decelerating = abs(target) < abs(cur) or (cur != 0 and (target * cur) < 0)
        step = decel_step if decelerating else accel_step
        if target > cur:
            return min(cur + step, target)
        return max(cur - step, target)

    def _now(self):
        return self.get_clock().now().nanoseconds * 1e-9


def main(args=None):
    rclpy.init(args=args)
    node = SafetyGateNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()