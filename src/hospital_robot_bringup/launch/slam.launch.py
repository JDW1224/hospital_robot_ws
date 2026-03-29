"""
SLAM 지도 생성 런치 파일
- lifecycle 자동 활성화 포함
"""
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import ExecuteProcess, TimerAction
from launch.substitutions import Command
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():

    pkg_description = get_package_share_directory('hospital_robot_description')
    pkg_bringup = get_package_share_directory('hospital_robot_bringup')

    xacro_file = os.path.join(pkg_description, 'urdf', 'robot.urdf.xacro')
    world_file = os.path.join(pkg_description, 'worlds', 'hospital_corridor.world')
    slam_params = os.path.join(pkg_bringup, 'config', 'slam_params.yaml')
    rviz_config = os.path.join(pkg_bringup, 'rviz', 'slam.rviz')

    robot_description = ParameterValue(Command(['xacro ', xacro_file]), value_type=str)

    spawn_x, spawn_y, spawn_z, spawn_yaw = '0.0', '-8.0', '0.5', '1.5708'

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

    # ── ros_gz bridge (clock 제외) ──
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

    # ── clock bridge (별도, 리맵) ──
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

    # ── slam_toolbox ──
    slam_toolbox = TimerAction(
        period=5.0,
        actions=[
            Node(
                package='slam_toolbox',
                executable='async_slam_toolbox_node',
                name='slam_toolbox',
                output='screen',
                parameters=[
                    slam_params,
                    {'use_sim_time': True},
                ],
            ),
        ],
    )

    # ── slam_toolbox lifecycle 자동 활성화 ──
    slam_configure = TimerAction(
        period=8.0,
        actions=[
            ExecuteProcess(
                cmd=['ros2', 'lifecycle', 'set', '/slam_toolbox', 'configure'],
                output='screen',
            ),
        ],
    )

    slam_activate = TimerAction(
        period=10.0,
        actions=[
            ExecuteProcess(
                cmd=['ros2', 'lifecycle', 'set', '/slam_toolbox', 'activate'],
                output='screen',
            ),
        ],
    )

    # ── RViz2 ──
    rviz = TimerAction(
        period=11.0,
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
        gz_sim,
        robot_state_pub,
        spawn_robot,
        bridge,
        clock_bridge,
        scan_remapper,
        slam_toolbox,
        slam_configure,
        slam_activate,
        rviz,
    ])