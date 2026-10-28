"""
실제 휠체어 로봇용 SLAM Toolbox launch
- 센서: RPLidar + OpenCR IMU + 휠 엔코더
- 환경: 병원 실내 (흰색 폼보드 환경 테스트 기준)
"""
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    pkg_bringup = get_package_share_directory('hospital_robot_bringup')
    slam_params_file = os.path.join(
        pkg_bringup, 'config', 'slam_toolbox_real.yaml'
    )
    
    # SLAM Toolbox 비동기 노드
    slam_toolbox_node = Node(
        package='slam_toolbox',
        executable='async_slam_toolbox_node',
        name='slam_toolbox',
        output='screen',
        parameters=[
            slam_params_file,
            {'use_sim_time': False}
        ]
    )
    
    return LaunchDescription([
        slam_toolbox_node,
    ])