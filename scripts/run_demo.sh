#!/bin/bash
# 공개심사 시연 원커맨드 기동
echo "=========================================="
echo " 병원 자율주행 로봇 — 시연 모드 기동"
echo "=========================================="
source ~/hospital_robot_ws/install/setup.bash
ros2 launch hospital_robot_bringup demo.launch.py
