import os
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='hospital_robot_perception',
            executable='yolo_detector',
            name='yolo_detector_node',
            output='screen',
            parameters=[{
                'model_path': os.path.expanduser(os.environ.get(
                    'HOSPITAL_ROBOT_MODEL', '~/hospital_robot_ws/models/best.pt')),  # ★ 실제 best.pt 경로로 수정
                'image_topic': '/image_raw',
                'process_hz': 3.0,
                'imgsz': 320,
            }],
        ),
        Node(
            package='hospital_robot_perception',
            executable='safety_gate',
            name='safety_gate_node',
            output='screen',
        ),
    ])
