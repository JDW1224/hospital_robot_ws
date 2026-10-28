#!/usr/bin/env python3
"""
safety_gate 노드 — 부드러운 정지/재출발 게이트 (휠체어용)

★ 현재 시스템 토폴로지에 맞춤:
  navigation.launch.py 84줄을  SetRemap('/cmd_vel', '/cmd_vel_nav') 로 수정한 뒤,
  이 게이트가 /cmd_vel_nav 를 받아 /cmd_vel_hc 로 발행 (바퀴는 /cmd_vel_hc 구독, 변경 없음)

  Nav2 --(/cmd_vel_nav)--> [safety_gate] --(/cmd_vel_hc)--> OpenCR 바퀴
                                ↑
              /perception/human_detected (Bool)

동작:
  - 사람 감지 ON  → cmd를 감속도 제한으로 0까지 램프다운 (급정지 X, 휠체어 승차감)
  - 사람 사라짐   → clear_hold_sec(기본 2초) 기다렸다가 부드럽게 재출발 (깜빡임 떨림 방지)
  - Nav2 goal은 취소하지 않음 → 게이트만 닫았다 열면 Nav2가 이어서 주행
  - Nav2 cmd가 cmd_timeout 동안 끊기면 안전상 0으로 램프

주의: 사람이 movement_time_allowance(25초) 이상 막으면 Nav2가 goal을 abort할 수 있음.
      goal_sender가 재동기화하므로 시스템은 회복되지만, 시연에선 15초 내 비켜주는 시나리오 권장.

실행:
  ros2 run hospital_robot_perception safety_gate
"""
import rclpy
from rclpy.node import Node
from std_msgs.msg import Bool
from geometry_msgs.msg import Twist


class SafetyGateNode(Node):
    def __init__(self):
        super().__init__('safety_gate_node')

        # ── 파라미터 ──
        self.declare_parameter('control_hz', 20.0)
        self.declare_parameter('max_accel', 0.3)        # m/s^2 재출발 가속 (부드럽게)
        self.declare_parameter('max_decel', 0.4)        # m/s^2 정지 감속 (휠체어 승차감 핵심)
        self.declare_parameter('max_ang_accel', 0.8)    # rad/s^2
        self.declare_parameter('max_ang_decel', 1.2)    # rad/s^2
        self.declare_parameter('clear_hold_sec', 2.0)   # 사람 사라진 뒤 대기
        self.declare_parameter('cmd_timeout_sec', 0.5)
        self.declare_parameter('in_topic', '/cmd_vel_nav')
        self.declare_parameter('out_topic', '/cmd_vel_hc')

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

        # ── 상태 ──
        self.nav_v = 0.0
        self.nav_w = 0.0
        self.last_cmd_t = -1e9
        self.out_v = 0.0
        self.out_w = 0.0
        self.human_now = False
        self.last_human_t = -1e9
        self._stopped_logged = False

        # ── 통신 ──
        self.sub_cmd = self.create_subscription(Twist, in_topic, self.on_cmd, 10)
        self.sub_human = self.create_subscription(
            Bool, '/perception/human_detected', self.on_human, 10)
        self.pub_cmd = self.create_publisher(Twist, out_topic, 10)
        self.timer = self.create_timer(1.0 / self.hz, self.on_tick)

        self.get_logger().info(
            f'safety_gate 시작: {in_topic} → {out_topic} '
            f'(decel {self.max_decel} m/s², 재출발 대기 {self.clear_hold}s)')

    def on_cmd(self, msg: Twist):
        self.nav_v = msg.linear.x
        self.nav_w = msg.angular.z
        self.last_cmd_t = self._now()

    def on_human(self, msg: Bool):
        self.human_now = bool(msg.data)
        if self.human_now:
            self.last_human_t = self._now()

    def on_tick(self):
        now = self._now()
        dt = 1.0 / self.hz

        # 히스테리시스: 지금 보이거나, 사라진 지 clear_hold 안이면 정지 유지
        stop_active = self.human_now or (now - self.last_human_t) < self.clear_hold
        cmd_fresh = (now - self.last_cmd_t) <= self.cmd_timeout

        if stop_active or not cmd_fresh:
            target_v, target_w = 0.0, 0.0
        else:
            target_v, target_w = self.nav_v, self.nav_w

        # 가/감속도 제한 램프 (부드러움의 핵심)
        self.out_v = self._ramp(self.out_v, target_v, self.max_accel * dt, self.max_decel * dt)
        self.out_w = self._ramp(self.out_w, target_w, self.max_ang_accel * dt, self.max_ang_decel * dt)

        out = Twist()
        out.linear.x = self.out_v
        out.angular.z = self.out_w
        self.pub_cmd.publish(out)

        # 상태 로그 (전이 시 1회)
        if stop_active and not self._stopped_logged:
            self.get_logger().info('🛑 사람 감지 → 부드러운 정지')
            self._stopped_logged = True
        elif not stop_active and self._stopped_logged:
            self.get_logger().info('✅ 경로 비워짐 → 재출발')
            self._stopped_logged = False

    @staticmethod
    def _ramp(cur, target, accel_step, decel_step):
        if target == cur:
            return cur
        decelerating = abs(target) < abs(cur) or (cur != 0 and (target * cur) < 0)
        step = decel_step if decelerating else accel_step
        return min(cur + step, target) if target > cur else max(cur - step, target)

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
        # 종료 시 정지 명령 한 번 (바퀴 안전)
        try:
            node.pub_cmd.publish(Twist())
        except Exception:
            pass
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
