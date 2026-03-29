#!/bin/bash
# POI 등록 모드 기동
source ~/hospital_robot_ws/install/setup.bash
ros2 launch hospital_robot_bringup poi_register.launch.py
