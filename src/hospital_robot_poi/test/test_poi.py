#!/usr/bin/env python3
"""POI Manager & Destination Parser 단위 테스트"""
import os
import tempfile
import pytest
import yaml

# 프로젝트 모듈 import
import sys
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))
from hospital_robot_poi.poi_manager import POIManager
from hospital_robot_poi.destination_parser import DestinationParser


@pytest.fixture
def sample_yaml(tmp_path):
    """테스트용 destinations.yaml 생성"""
    data = {
        'frame_id': 'map',
        'destinations': [
            {'id': '301', 'name': '301호', 'x': 5.2, 'y': 3.1, 'yaw': 1.5708},
            {'id': '302', 'name': '302호', 'x': 7.8, 'y': 3.1, 'yaw': 1.5708},
            {'id': 'elevator', 'name': '엘리베이터', 'x': 0.0, 'y': -4.5, 'yaw': 3.14},
            {'id': 'entrance', 'name': '출입구', 'x': 0.0, 'y': -8.0, 'yaw': 0.0},
        ],
    }
    filepath = str(tmp_path / 'destinations.yaml')
    with open(filepath, 'w') as f:
        yaml.dump(data, f, allow_unicode=True)
    return filepath


# ═══════════════════════════════════
#  POIManager 테스트
# ═══════════════════════════════════

class TestPOIManager:
    def test_load(self, sample_yaml):
        mgr = POIManager(sample_yaml)
        assert mgr.count() == 4

    def test_get_by_id(self, sample_yaml):
        mgr = POIManager(sample_yaml)
        poi = mgr.get('301')
        assert poi is not None
        assert poi['name'] == '301호'
        assert poi['x'] == 5.2

    def test_get_missing(self, sample_yaml):
        mgr = POIManager(sample_yaml)
        assert mgr.get('999') is None

    def test_get_by_name(self, sample_yaml):
        mgr = POIManager(sample_yaml)
        poi = mgr.get_by_name('엘리베이터')
        assert poi is not None
        assert poi['id'] == 'elevator'

    def test_get_all(self, sample_yaml):
        mgr = POIManager(sample_yaml)
        all_pois = mgr.get_all()
        assert len(all_pois) == 4
        # 원본 수정 방지
        all_pois[0]['x'] = 999
        assert mgr.get('301')['x'] == 5.2

    def test_get_ids(self, sample_yaml):
        mgr = POIManager(sample_yaml)
        ids = mgr.get_ids()
        assert '301' in ids
        assert 'elevator' in ids

    def test_yaw_to_quaternion(self, sample_yaml):
        mgr = POIManager(sample_yaml)
        q = mgr.yaw_to_quaternion(0.0)
        assert abs(q['w'] - 1.0) < 0.001
        assert abs(q['z'] - 0.0) < 0.001

    def test_file_not_found(self):
        with pytest.raises(FileNotFoundError):
            POIManager('/nonexistent/path.yaml')

    def test_duplicate_id(self, tmp_path):
        data = {
            'frame_id': 'map',
            'destinations': [
                {'id': '301', 'name': 'A', 'x': 0, 'y': 0, 'yaw': 0},
                {'id': '301', 'name': 'B', 'x': 1, 'y': 1, 'yaw': 0},
            ],
        }
        filepath = str(tmp_path / 'dup.yaml')
        with open(filepath, 'w') as f:
            yaml.dump(data, f)
        with pytest.raises(ValueError, match='중복'):
            POIManager(filepath)

    def test_missing_field(self, tmp_path):
        data = {
            'frame_id': 'map',
            'destinations': [
                {'id': '301', 'name': 'A', 'x': 0},  # y, yaw 누락
            ],
        }
        filepath = str(tmp_path / 'bad.yaml')
        with open(filepath, 'w') as f:
            yaml.dump(data, f)
        with pytest.raises(ValueError, match='누락'):
            POIManager(filepath)


# ═══════════════════════════════════
#  DestinationParser 테스트
# ═══════════════════════════════════

class TestDestinationParser:
    def test_exact_id(self, sample_yaml):
        mgr = POIManager(sample_yaml)
        parser = DestinationParser(mgr)
        assert parser.parse('301') == '301'

    def test_exact_name(self, sample_yaml):
        mgr = POIManager(sample_yaml)
        parser = DestinationParser(mgr)
        assert parser.parse('엘리베이터') == 'elevator'

    def test_with_ho_suffix(self, sample_yaml):
        mgr = POIManager(sample_yaml)
        parser = DestinationParser(mgr)
        assert parser.parse('301호') == '301'

    def test_korean_numbers(self, sample_yaml):
        mgr = POIManager(sample_yaml)
        parser = DestinationParser(mgr)
        assert parser.parse('삼공일') == '301'
        assert parser.parse('삼공이호') == '302'

    def test_partial_match(self, sample_yaml):
        mgr = POIManager(sample_yaml)
        parser = DestinationParser(mgr)
        assert parser.parse('엘리') == 'elevator'

    def test_no_match(self, sample_yaml):
        mgr = POIManager(sample_yaml)
        parser = DestinationParser(mgr)
        assert parser.parse('999호') is None

    def test_empty_input(self, sample_yaml):
        mgr = POIManager(sample_yaml)
        parser = DestinationParser(mgr)
        assert parser.parse('') is None
        assert parser.parse(None) is None


if __name__ == '__main__':
    pytest.main([__file__, '-v'])
