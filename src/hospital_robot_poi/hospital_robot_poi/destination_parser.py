#!/usr/bin/env python3
"""
Destination Parser
- 사용자 입력을 정규화하여 POI ID로 변환
- "301호", "301", "삼공일호" → "301"
- 웹 UI나 음성 입력에서 들어오는 다양한 형식 처리

사용 예:
    from hospital_robot_poi.destination_parser import DestinationParser
    parser = DestinationParser(poi_manager)
    poi_id = parser.parse("301호")  # → "301"
"""
import re
from typing import Optional


# 한글 숫자 매핑
KOREAN_NUMS = {
    '일': '1', '이': '2', '삼': '3', '사': '4', '오': '5',
    '육': '6', '칠': '7', '팔': '8', '구': '9', '공': '0',
    '영': '0',
}


class DestinationParser:
    def __init__(self, poi_manager):
        self.poi_manager = poi_manager

    def parse(self, user_input: str) -> Optional[str]:
        """
        사용자 입력 → POI ID 변환
        반환: 매칭된 POI ID, 없으면 None
        """
        if not user_input:
            return None

        text = user_input.strip()

        # 1. 정확히 ID 일치
        if self.poi_manager.get(text):
            return text

        # 2. 정확히 이름 일치
        poi = self.poi_manager.get_by_name(text)
        if poi:
            return poi['id']

        # 3. "호" 제거 후 매칭 (301호 → 301)
        cleaned = re.sub(r'호$', '', text)
        if cleaned != text and self.poi_manager.get(cleaned):
            return cleaned

        # 4. 한글 숫자 변환 (삼공일 → 301)
        converted = self._korean_to_number(text)
        if converted and self.poi_manager.get(converted):
            return converted

        # 한글 숫자 + "호" 제거
        converted_clean = re.sub(r'호$', '', converted) if converted else None
        if converted_clean and self.poi_manager.get(converted_clean):
            return converted_clean

        # 5. 부분 매칭 (이름에 포함)
        text_lower = text.lower()
        for poi_data in self.poi_manager.get_all():
            if text_lower in poi_data['name'].lower():
                return poi_data['id']
            if text_lower in poi_data['id'].lower():
                return poi_data['id']

        return None

    def _korean_to_number(self, text: str) -> Optional[str]:
        """한글 숫자를 아라비아 숫자로 변환"""
        result = []
        has_korean = False
        for char in text:
            if char in KOREAN_NUMS:
                result.append(KOREAN_NUMS[char])
                has_korean = True
            else:
                result.append(char)
        return ''.join(result) if has_korean else None
