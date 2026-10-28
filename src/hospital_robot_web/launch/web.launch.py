"""
병원 휠체어 웹 서버 launch
- web_server_node 실행 (노트북에서)

사용:
  ros2 launch hospital_robot_web web.launch.py

전제:
  - ROS_DOMAIN_ID=9 (젯슨과 동일)
  - 젯슨에서 goal_sender 실행 중이어야 명령이 전달됨
"""
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='hospital_robot_web',
            executable='web_server',
            name='web_server_node',
            output='screen',
        ),
    ])
