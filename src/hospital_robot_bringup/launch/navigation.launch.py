"""
네비게이션 런치 파일
- Gz Sim + 로봇 스폰
- map_server (저장된 맵 로드)
- AMCL (위치추정)
- Nav2 (자율주행)
- RViz

사용법:
  ros2 launch hospital_robot_bringup navigation.launch.py map:=/full/path/to/map.yaml
"""
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument, ExecuteProcess, TimerAction, IncludeLaunchDescription
)
from launch.substitutions import Command, LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():

    pkg_description = get_package_share_directory('hospital_robot_description')
    pkg_bringup = get_package_share_directory('hospital_robot_bringup')

    xacro_file = os.path.join(pkg_description, 'urdf', 'robot.urdf.xacro')
    world_file = os.path.join(pkg_description, 'worlds', 'hospital_corridor.world')
    nav2_params = os.path.join(pkg_bringup, 'config', 'nav2_params.yaml')
    rviz_config = os.path.join(pkg_bringup, 'rviz', 'navigation.rviz')

    default_map = os.path.expanduser('~/hospital_robot_ws/maps/hospital_floor1.yaml')

    robot_description = ParameterValue(Command(['xacro ', xacro_file]), value_type=str)

    spawn_x, spawn_y, spawn_z, spawn_yaw = '0.0', '-8.0', '0.5', '1.5708'

    # ── 런치 인자 ──
    map_arg = DeclareLaunchArgument(
        'map',
        default_value=default_map,
        description='Full path to map yaml file',
    )

    # ── Gz Sim ──
    gz_sim = ExecuteProcess(
        cmd=['gz', 'sim', '-r', world_file],
        output='screen',
    )

    # ── robot_state_publisher ──
    robot_state_pub = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description': robot_description}],
        output='screen',
    )

    # ── 로봇 스폰 ──
    spawn_robot = TimerAction(
        period=2.0,
        actions=[
            Node(
                package='ros_gz_sim',
                executable='create',
                arguments=[
                    '-name', 'hospital_robot',
                    '-topic', 'robot_description',
                    '-x', spawn_x, '-y', spawn_y,
                    '-z', spawn_z, '-Y', spawn_yaw,
                ],
                output='screen',
            ),
        ],
    )

    # ── ros_gz bridge ──
    bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        name='ros_gz_bridge',
        arguments=[
            '/cmd_vel@geometry_msgs/msg/Twist@gz.msgs.Twist',
            '/odom@nav_msgs/msg/Odometry@gz.msgs.Odometry',
            '/scan@sensor_msgs/msg/LaserScan@gz.msgs.LaserScan',
            '/tf@tf2_msgs/msg/TFMessage@gz.msgs.Pose_V',
            '/joint_states@sensor_msgs/msg/JointState@gz.msgs.Model',
        ],
        output='screen',
    )

    # ── clock bridge ──
    clock_bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        name='clock_bridge',
        arguments=[
            '/world/hospital_ward/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock',
        ],
        remappings=[
            ('/world/hospital_ward/clock', '/clock'),
        ],
        output='screen',
    )

    # ── scan frame_id 리맵 ──
    scan_remapper = TimerAction(
        period=3.0,
        actions=[
            Node(
                package='hospital_robot_navigation',
                executable='scan_frame_remapper',
                name='scan_frame_remapper',
                parameters=[{
                    'input_topic': '/scan',
                    'output_topic': '/scan_fixed',
                    'target_frame': 'lidar_link',
                    'use_sim_time': True,
                }],
                output='screen',
            ),
        ],
    )

    # ── Nav2 (map_server + AMCL + planner + controller + bt_navigator) ──
    nav2_bringup = TimerAction(
        period=5.0,
        actions=[
            IncludeLaunchDescription(
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
                    'use_sim_time': 'true',
                    'autostart': 'true',
                }.items(),
            ),
        ],
    )

    # ── RViz2 ──
    rviz = TimerAction(
        period=10.0,
        actions=[
            Node(
                package='rviz2',
                executable='rviz2',
                arguments=['-d', rviz_config] if os.path.exists(rviz_config) else [],
                parameters=[{'use_sim_time': True}],
                output='screen',
            ),
        ],
    )

    return LaunchDescription([
        map_arg,
        gz_sim,
        robot_state_pub,
        spawn_robot,
        bridge,
        clock_bridge,
        scan_remapper,
        nav2_bringup,
        rviz,
    ])
