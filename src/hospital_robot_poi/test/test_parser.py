"""destination_parser 단위 테스트"""
import pytest
from hospital_robot_poi.destination_parser import normalize_input, extract_destination_id

REGISTERED_IDS = ["301", "302", "303", "entrance", "elevator", "admission"]


class TestNormalizeInput:
    def test_basic(self):
        assert normalize_input("  301호로 가  ") == "301호"

    def test_suffix_removal(self):
        assert normalize_input("301호로 가줘") == "301호"
        assert normalize_input("301 가") == "301"
        assert normalize_input("엘리베이터로 이동") == "엘리베이터"

    def test_whitespace(self):
        assert normalize_input("  301  호 로  가  ") == "301 호"


class TestExtractDestinationId:
    def test_room_number(self):
        assert extract_destination_id("301호로 가", REGISTERED_IDS) == "301"
        assert extract_destination_id("301 가줘", REGISTERED_IDS) == "301"
        assert extract_destination_id("302로 이동", REGISTERED_IDS) == "302"

    def test_keyword(self):
        assert extract_destination_id("엘리베이터로 가", REGISTERED_IDS) == "elevator"
        assert extract_destination_id("출입구 가줘", REGISTERED_IDS) == "entrance"
        assert extract_destination_id("원무과로 이동", REGISTERED_IDS) == "admission"

    def test_direct_id(self):
        assert extract_destination_id("entrance", REGISTERED_IDS) == "entrance"
        assert extract_destination_id("301", REGISTERED_IDS) == "301"

    def test_not_registered(self):
        assert extract_destination_id("999호로 가", REGISTERED_IDS) is None
        assert extract_destination_id("화장실", REGISTERED_IDS) is None

    def test_empty(self):
        assert extract_destination_id("", REGISTERED_IDS) is None
        assert extract_destination_id("가줘", REGISTERED_IDS) is None


if __name__ == '__main__':
    pytest.main([__file__, '-v'])
