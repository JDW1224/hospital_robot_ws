#!/usr/bin/env python3
"""
POI 등록 노드 v2
- RViz에서 Publish Point 클릭 → 자동 번호 매겨서 저장
- 터미널 입력 불필요 (런치에서 stdin 문제 회피)
- 나중에 destinations.yaml에서 name 수정 가능

사용법:
  1. ros2 launch hospital_robot_bringup poi_register.launch.py
  2. RViz 상단 "Publish Point" 클릭
  3. 지도에서 목적지 위치를 순서대로 클릭
  4. 자동으로 poi_001, poi_002... 로 저장됨
  5. 종료 후 destinations.yaml에서 id/name 수정

파라미터:
  - output_file: 저장 경로
  - default_yaw: 기본 방향 (라디안, 기본 0.0)
  - prefix: ID 접두사 (기본 "poi")
"""
import os
import math

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PointStamped
import yaml


class POIRegistrar(Node):
    def __init__(self):
        super().__init__('poi_registrar')

        # 파라미터
        self.declare_parameter('output_file', os.path.expanduser(
            '~/hospital_robot_ws/src/hospital_robot_poi/poi/destinations.yaml'
        ))
        self.declare_parameter('frame_id', 'map')
        self.declare_parameter('default_yaw', 0.0)
        self.declare_parameter('prefix', 'poi')

        self.output_file = self.get_parameter('output_file').value
        self.frame_id = self.get_parameter('frame_id').value
        self.default_yaw = self.get_parameter('default_yaw').value
        self.prefix = self.get_parameter('prefix').value

        # 기존 데이터 로드
        self.destinations = self._load_existing()
        self.click_count = len(self.destinations)

        # /clicked_point 구독
        self.sub = self.create_subscription(
            PointStamped,
            '/clicked_point',
            self.point_callback,
            10,
        )

        self.get_logger().info('='*50)
        self.get_logger().info('POI 등록 도구 v2')
        self.get_logger().info(f'저장 위치: {self.output_file}')
        self.get_logger().info(f'현재 등록된 POI: {self.click_count}개')
        self.get_logger().info(f'기본 방향(yaw): {math.degrees(self.default_yaw):.0f}°')
        self.get_logger().info('')
        self.get_logger().info('RViz에서 "Publish Point" 클릭 후 지도 클릭!')
        self.get_logger().info('클릭할 때마다 자동 저장됩니다.')
        self.get_logger().info('종료 후 destinations.yaml에서 이름 수정 가능')
        self.get_logger().info('='*50)
        self._print_existing()

    def _load_existing(self):
        """기존 destinations.yaml 로드"""
        if os.path.exists(self.output_file):
            try:
                with open(self.output_file, 'r') as f:
                    data = yaml.safe_load(f)
                if data and 'destinations' in data and isinstance(data['destinations'], list):
                    return data['destinations']
            except Exception as e:
                self.get_logger().warn(f'기존 파일 로드 실패: {e}')
        return []

    def _print_existing(self):
        """등록된 POI 목록 출력"""
        if self.destinations:
            self.get_logger().info('')
            self.get_logger().info('── 기존 POI 목록 ──')
            for d in self.destinations:
                yaw_deg = math.degrees(d.get('yaw', 0))
                self.get_logger().info(
                    f"  [{d['id']}] {d.get('name', d['id'])} → "
                    f"x={d['x']:.2f}, y={d['y']:.2f}, yaw={yaw_deg:.0f}°"
                )
            self.get_logger().info('')

    def point_callback(self, msg: PointStamped):
        """RViz에서 클릭한 좌표 수신 → 자동 저장"""
        self.click_count += 1
        x = round(msg.point.x, 3)
        y = round(msg.point.y, 3)

        poi_id = f'{self.prefix}_{self.click_count:03d}'
        poi_name = f'{self.prefix}_{self.click_count:03d}'

        entry = {
            'id': poi_id,
            'name': poi_name,
            'x': x,
            'y': y,
            'yaw': self.default_yaw,
        }
        self.destinations.append(entry)
        self._save()

        self.get_logger().info(
            f'✅ [{self.click_count}] {poi_id} 등록: '
            f'x={x:.3f}, y={y:.3f} '
            f'(총 {len(self.destinations)}개)'
        )

    def _save(self):
        """destinations.yaml 저장"""
        os.makedirs(os.path.dirname(self.output_file), exist_ok=True)

        data = {
            'frame_id': self.frame_id,
            'destinations': self.destinations,
        }

        with open(self.output_file, 'w') as f:
            yaml.dump(data, f, default_flow_style=False, allow_unicode=True, sort_keys=False)


def main(args=None):
    rclpy.init(args=args)
    node = POIRegistrar()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info(f'POI 등록 종료 (총 {len(node.destinations)}개)')
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
