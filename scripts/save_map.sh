#!/bin/bash
# SLAM 후 지도 저장
MAP_NAME=${1:-hospital_floor1}
ros2 run nav2_map_server map_saver_cli -f ~/hospital_robot_ws/maps/$MAP_NAME
echo "지도 저장 완료: ~/hospital_robot_ws/maps/$MAP_NAME"
