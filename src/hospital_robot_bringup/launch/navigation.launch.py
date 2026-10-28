"""
실제 로봇 Nav2 + AMCL 자율주행 launch
- use_sim_time=false
- 저장된 맵 로드
- AMCL + map_server + Nav2 stack

사용법:
  # 기본 맵 사용 (~/hospital_robot_ws/maps/hospital_map.yaml)
  ros2 launch hospital_robot_bringup navigation.launch.py

  # 다른 맵 사용
  ros2 launch hospital_robot_bringup navigation.launch.py \\
      map:=/absolute/path/to/map.yaml

전제조건:
  먼저 view_sensors.launch.py를 다른 터미널에서 실행 중이어야 함
"""
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument, GroupAction, IncludeLaunchDescription, TimerAction
)
from launch_ros.actions import SetRemap
from launch.substitutions import LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node


def generate_launch_description():

    pkg_bringup = get_package_share_directory('hospital_robot_bringup')
    nav2_params = os.path.join(pkg_bringup, 'config', 'nav2_params.yaml')
    rviz_config = os.path.join(pkg_bringup, 'rviz', 'navigation.rviz')

    default_map = os.path.expanduser('~/hospital_robot_ws/maps/hospital_map.yaml')

    # ── launch 인자 ──
    map_arg = DeclareLaunchArgument(
        'map',
        default_value=default_map,
        description='Full path to map yaml file',
    )

    use_rviz_arg = DeclareLaunchArgument(
        'use_rviz',
        default_value='true',
        description='RViz2 켜기',
    )

    # ── Nav2 (map_server + AMCL + planner + controller + bt_navigator) ──
    nav2_bringup = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                get_package_share_directory('nav2_bringup'),
                'launch',
                'bringup_launch.py',
            )
        ),
        launch_arguments={
            'map': LaunchConfiguration('map'),
            'params_file': nav2_params,
            'use_sim_time': 'false',
            'autostart': 'true',
        }.items(),
    )

    # ── RViz2 (3초 후) ──
    rviz = TimerAction(
        period=3.0,
        actions=[
            Node(
                package='rviz2',
                executable='rviz2',
                arguments=['-d', rviz_config] if os.path.exists(rviz_config) else [],
                parameters=[{'use_sim_time': False}],
                output='screen',
            ),
        ],
    )

    # Nav2의 /cmd_vel 출력을 turtlebot3가 구독 중인 /cmd_vel_hc로 리맵
    nav2_group = GroupAction([
        SetRemap('/cmd_vel', '/cmd_vel_hc'),
        nav2_bringup,
    ])

    return LaunchDescription([
        map_arg,
        use_rviz_arg,
        nav2_group,
        rviz,
    ])