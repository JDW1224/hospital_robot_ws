"""POI Manager 단위 테스트"""
import pytest
import os
import yaml
import math
import tempfile
from hospital_robot_poi.poi_manager import POIManager, POI, yaw_to_quaternion


@pytest.fixture
def sample_yaml(tmp_path):
    """테스트용 임시 POI YAML 생성"""
    data = {
        'frame_id': 'map',
        'destinations': [
            {'id': '301', 'name': '301호', 'x': 12.5, 'y': 3.2, 'yaw': 1.5708},
            {'id': 'entrance', 'name': '출입구', 'x': 0.5, 'y': 0.0, 'yaw': 0.0},
        ]
    }
    path = tmp_path / "test_destinations.yaml"
    with open(path, 'w') as f:
        yaml.dump(data, f)
    return str(path)


class TestYawToQuaternion:
    def test_zero(self):
        qx, qy, qz, qw = yaw_to_quaternion(0.0)
        assert qx == 0.0
        assert qy == 0.0
        assert abs(qz) < 1e-9
        assert abs(qw - 1.0) < 1e-9

    def test_90deg(self):
        qx, qy, qz, qw = yaw_to_quaternion(math.pi / 2)
        assert abs(qz - math.sin(math.pi / 4)) < 1e-6
        assert abs(qw - math.cos(math.pi / 4)) < 1e-6


class TestPOIManager:
    def test_load(self, sample_yaml):
        manager = POIManager(sample_yaml)
        assert len(manager.pois) == 2
        assert "301" in manager.get_registered_ids()
        assert "entrance" in manager.get_registered_ids()

    def test_lookup(self, sample_yaml):
        manager = POIManager(sample_yaml)
        poi = manager.lookup("301")
        assert poi is not None
        assert poi.x == 12.5
        assert poi.name == "301호"

    def test_lookup_missing(self, sample_yaml):
        manager = POIManager(sample_yaml)
        assert manager.lookup("999") is None

    def test_to_goal_pose(self, sample_yaml):
        manager = POIManager(sample_yaml)
        goal = manager.to_goal_pose("301")
        assert goal is not None
        assert goal.frame_id == "map"
        assert goal.x == 12.5
        # quaternion 검증
        assert abs(goal.qx) < 1e-9
        assert abs(goal.qy) < 1e-9

    def test_add_poi(self, sample_yaml):
        manager = POIManager(sample_yaml)
        new_poi = POI(id="302", name="302호", x=15.0, y=3.2, yaw=1.5708)
        manager.add_poi(new_poi)
        assert manager.lookup("302") is not None
        # 파일에도 저장됐는지 확인
        manager2 = POIManager(sample_yaml)
        assert manager2.lookup("302") is not None

    def test_file_not_found(self):
        with pytest.raises(FileNotFoundError):
            POIManager("/nonexistent/path.yaml")

    def test_registered_list(self, sample_yaml):
        manager = POIManager(sample_yaml)
        lst = manager.get_registered_list()
        assert len(lst) == 2
        assert any(p['id'] == '301' for p in lst)


if __name__ == '__main__':
    pytest.main([__file__, '-v'])
