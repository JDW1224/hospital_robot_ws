#!/usr/bin/env python3
"""
POI Manager
- destinations.yaml 로드/조회/유효성 검사
- 다른 노드(goal_sender, web_server)에서 import하여 사용

사용 예:
    from hospital_robot_poi.poi_manager import POIManager
    mgr = POIManager('/path/to/destinations.yaml')
    poi = mgr.get('301')  # {'id': '301', 'name': '301호', 'x': 5.2, ...}
    all_pois = mgr.get_all()
"""
import os
import math
import yaml
from typing import Optional


class POIManager:
    def __init__(self, yaml_path: str = None):
        if yaml_path is None:
            yaml_path = os.path.expanduser(
                '~/hospital_robot_ws/src/hospital_robot_poi/poi/destinations.yaml'
            )
        self.yaml_path = yaml_path
        self.frame_id = 'map'
        self.destinations = []
        self.load()

    def load(self):
        """YAML 파일에서 POI 목록 로드"""
        if not os.path.exists(self.yaml_path):
            raise FileNotFoundError(f'POI 파일 없음: {self.yaml_path}')

        with open(self.yaml_path, 'r') as f:
            data = yaml.safe_load(f)

        if not data or 'destinations' not in data:
            raise ValueError(f'잘못된 POI 파일 형식: {self.yaml_path}')

        self.frame_id = data.get('frame_id', 'map')
        self.destinations = data['destinations']
        self._validate()

    def _validate(self):
        """POI 데이터 유효성 검사"""
        ids = set()
        for d in self.destinations:
            # 필수 필드 확인
            for key in ['id', 'name', 'x', 'y', 'yaw']:
                if key not in d:
                    raise ValueError(f"POI에 '{key}' 필드 누락: {d}")

            # 중복 ID 확인
            if d['id'] in ids:
                raise ValueError(f"중복 POI ID: {d['id']}")
            ids.add(d['id'])

            # 숫자 타입 확인
            for key in ['x', 'y', 'yaw']:
                if not isinstance(d[key], (int, float)):
                    raise ValueError(f"POI '{d['id']}'의 '{key}'가 숫자가 아님: {d[key]}")

    def get(self, poi_id: str) -> Optional[dict]:
        """ID로 POI 조회. 없으면 None"""
        for d in self.destinations:
            if d['id'] == poi_id:
                return d.copy()
        return None

    def get_by_name(self, name: str) -> Optional[dict]:
        """이름으로 POI 조회. 없으면 None"""
        for d in self.destinations:
            if d['name'] == name:
                return d.copy()
        return None

    def get_all(self) -> list:
        """전체 POI 목록 반환"""
        return [d.copy() for d in self.destinations]

    def get_ids(self) -> list:
        """등록된 ID 목록"""
        return [d['id'] for d in self.destinations]

    def get_names(self) -> list:
        """등록된 이름 목록"""
        return [d['name'] for d in self.destinations]

    def count(self) -> int:
        """등록된 POI 수"""
        return len(self.destinations)

    @staticmethod
    def yaw_to_quaternion(yaw: float) -> dict:
        """yaw(rad) → quaternion 변환"""
        return {
            'x': 0.0,
            'y': 0.0,
            'z': math.sin(yaw / 2.0),
            'w': math.cos(yaw / 2.0),
        }

    def __repr__(self):
        return f'POIManager({self.count()} POIs from {self.yaml_path})'
