#!/usr/bin/env python3
"""
YOLO 사람(human_model) 감지 노드 — 젯슨 저부하 버전
- 입력: /image_raw (v4l2_camera, view_sensors.launch.py가 발행)
- 출력:
    /perception/human_detected   (std_msgs/Bool)    ← safety_gate가 소비
    /perception/human_box_height (std_msgs/Float32) ← 디버그/거리 프록시(px)
- 판정: 화면 중앙 밴드(center_band) 안 + 박스높이 >= box_height_stop → 정지존
- 부하 대책: process_hz(기본 3Hz)로 추론 빈도 제한, imgsz 320

실행(젯슨):
  ros2 run hospital_robot_perception yolo_detector --ros-args -p model_path:=<absolute-path-to-best.pt>
"""
import os
import time

import rclpy
from rclpy.node import Node
from std_msgs.msg import Bool, Float32
from sensor_msgs.msg import Image

import cv2
from cv_bridge import CvBridge
from ultralytics import YOLO


class YoloDetectorNode(Node):
    def __init__(self):
        super().__init__('yolo_detector_node')

        # ── 파라미터 ──
        self.declare_parameter('model_path', os.path.expanduser(
            os.environ.get('HOSPITAL_ROBOT_MODEL', '~/hospital_robot_ws/models/best.pt')))
        self.declare_parameter('image_topic', '/image_raw')
        self.declare_parameter('process_hz', 3.0)        # 젯슨 부하 핵심: 추론 빈도
        self.declare_parameter('imgsz', 320)             # 젯슨 부하: 작은 입력
        # test_camera.py 검증값 그대로
        self.declare_parameter('conf_threshold', 0.70)
        self.declare_parameter('min_box_height', 100)
        self.declare_parameter('min_box_width', 30)
        self.declare_parameter('aspect_ratio_min', 1.3)
        # "앞 + 가까움" 정지존 판정
        self.declare_parameter('box_height_stop', 200)   # 박스높이 ≥ → 가까움
        self.declare_parameter('center_band', 0.30)      # 중앙 ±30% = 전방
        self.declare_parameter('confirm_frames', 2)      # N회 연속이어야 ON(오탐 차단)

        gp = self.get_parameter
        self.model_path = gp('model_path').value
        self.image_topic = gp('image_topic').value
        self.period = 1.0 / float(gp('process_hz').value)
        self.imgsz = int(gp('imgsz').value)
        self.conf = float(gp('conf_threshold').value)
        self.min_h = int(gp('min_box_height').value)
        self.min_w = int(gp('min_box_width').value)
        self.aspect_min = float(gp('aspect_ratio_min').value)
        self.box_h_stop = int(gp('box_height_stop').value)
        self.center_band = float(gp('center_band').value)
        self.confirm_frames = int(gp('confirm_frames').value)

        # ── 모델 ──
        self.get_logger().info(f'모델 로딩: {self.model_path}')
        self.model = YOLO(self.model_path)
        try:
            import torch
            self.device = 0 if torch.cuda.is_available() else 'cpu'
        except Exception:
            self.device = 'cpu'
        self.get_logger().info(f'클래스: {self.model.names} / device={self.device} / {1.0/self.period:.0f}Hz imgsz={self.imgsz}')

        # ── 통신 ──
        self.bridge = CvBridge()
        self.pub_detected = self.create_publisher(Bool, '/perception/human_detected', 10)
        self.pub_height = self.create_publisher(Float32, '/perception/human_box_height', 10)
        self.sub = self.create_subscription(Image, self.image_topic, self.on_image, 1)

        self._last_t = 0.0
        self._hit_streak = 0

    def on_image(self, msg: Image):
        # 추론 빈도 제한 (젯슨 부하 보호) — 나머지 프레임은 버림
        now = time.monotonic()
        if now - self._last_t < self.period:
            return
        self._last_t = now

        frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        h_img, w_img = frame.shape[:2]

        results = self.model.predict(
            frame, imgsz=self.imgsz, conf=self.conf,
            verbose=False, device=self.device)

        # test_camera.py 필터 그대로
        valid = []
        for box in results[0].boxes:
            x1, y1, x2, y2 = [float(v) for v in box.xyxy[0]]
            w, h = x2 - x1, y2 - y1
            if h < self.min_h or w < self.min_w:
                continue
            if (h / w if w > 0 else 0) < self.aspect_min:
                continue
            valid.append({'cx': (x1 + x2) / 2.0, 'h': h})

        in_stop_zone = False
        nearest_h = 0.0
        if valid:
            biggest = max(valid, key=lambda b: b['h'])
            nearest_h = biggest['h']
            in_center = abs(biggest['cx'] - w_img / 2.0) <= self.center_band * w_img
            close = biggest['h'] >= self.box_h_stop
            in_stop_zone = in_center and close

        # 디바운스: confirm_frames 연속이어야 True (단발 오탐 차단)
        self._hit_streak = self._hit_streak + 1 if in_stop_zone else 0
        detected = self._hit_streak >= self.confirm_frames

        m = Bool(); m.data = bool(detected); self.pub_detected.publish(m)
        mh = Float32(); mh.data = float(nearest_h); self.pub_height.publish(mh)

        if detected:
            self.get_logger().info(f'🛑 사람 감지 (박스높이 {nearest_h:.0f}px)', throttle_duration_sec=2.0)


def main(args=None):
    rclpy.init(args=args)
    node = YoloDetectorNode()
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
