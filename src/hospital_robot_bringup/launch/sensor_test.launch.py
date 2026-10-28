
import os
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    # 1. 라이다 노드 (이전에 설정한 포트 고정 이름 /dev/rplidar 사용)
    lidar_node = Node(
        package='sllidar_ros2',
        executable='sllidar_node',
        name='sllidar_node',
        parameters=[{
            'serial_port': '/dev/rplidar',
            'serial_baudrate': 460800,
            'frame_id': 'lidar_link',
            'inverted': False,
            'angle_compensate': True,
            'use_sim_time': False
        }],
        output='screen'
    )

    # 2. USB 웹캠 노드
    camera_node = Node(
        package='v4l2_camera',
        executable='v4l2_camera_node',
        name='camera_node',
        parameters=[{
            'video_device': '/dev/video1',
            'image_size': [640, 480],
            'camera_frame_id': 'camera_link',
            'use_sim_time': False
        }],
        output='screen'
    )

    return LaunchDescription([
        lidar_node,
        camera_node,
    ])
