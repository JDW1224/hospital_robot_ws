"""
POI 등록 런치 파일
- 저장된 맵 로드 (map_server)
- POI 등록 노드 (poi_registrar)
- RViz (Publish Point 도구)

사용법:
  ros2 launch hospital_robot_bringup poi_register.launch.py
  ros2 launch hospital_robot_bringup poi_register.launch.py map:=/path/to/map.yaml
"""
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, TimerAction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():

    pkg_bringup = get_package_share_directory('hospital_robot_bringup')
    default_map = os.path.expanduser('~/hospital_robot_ws/maps/hospital_map.yaml')
    rviz_config = os.path.join(pkg_bringup, 'rviz', 'poi_register.rviz')

    map_arg = DeclareLaunchArgument(
        'map', default_value=default_map,
        description='Full path to map yaml file',
    )

    # map_server
    map_server = Node(
        package='nav2_map_server',
        executable='map_server',
        name='map_server',
        output='screen',
        parameters=[{
            'yaml_filename': LaunchConfiguration('map'),
            'use_sim_time': False,
        }],
    )

    # map_server lifecycle 활성화
    map_activate = TimerAction(period=2.0, actions=[
        Node(
            package='nav2_lifecycle_manager',
            executable='lifecycle_manager',
            name='lifecycle_manager_map',
            output='screen',
            parameters=[{
                'use_sim_time': False,
                'autostart': True,
                'node_names': ['map_server'],
            }],
        ),
    ])

    # POI 등록 노드
    poi_registrar = TimerAction(period=3.0, actions=[
        Node(
            package='hospital_robot_poi',
            executable='poi_registrar',
            name='poi_registrar',
            output='screen',
            parameters=[{
                'use_sim_time': False,
            }],
        ),
    ])

    # RViz
    rviz = TimerAction(period=4.0, actions=[
        Node(
            package='rviz2',
            executable='rviz2',
            arguments=['-d', rviz_config] if os.path.exists(rviz_config) else [],
            parameters=[{'use_sim_time': False}],
            output='screen',
        ),
    ])

    return LaunchDescription([
        map_arg,
        map_server,
        map_activate,
        poi_registrar,
        rviz,
    ])
