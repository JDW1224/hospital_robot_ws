"""
병원 로봇 시뮬레이션 런치 파일
- Gz Sim 8 + hospital_corridor.world
- 로봇 스폰 (출입구 근처)
- ros_gz bridge (cmd_vel, odom, scan, camera, tf)
"""
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument, IncludeLaunchDescription,
    ExecuteProcess, RegisterEventHandler
)
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, Command
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():

    # ── 패키지 경로 ──
    pkg_description = get_package_share_directory('hospital_robot_description')

    # ── 파일 경로 ──
    xacro_file = os.path.join(pkg_description, 'urdf', 'robot.urdf.xacro')
    world_file = os.path.join(pkg_description, 'worlds', 'hospital_corridor.world')

    # ── URDF → robot_description ──
    robot_description = ParameterValue(Command(['xacro ', xacro_file]), value_type=str)

    # ── 로봇 스폰 위치 (출입구 앞) ──
    spawn_x = '0.0'
    spawn_y = '-8.0'
    spawn_z = '0.1'
    spawn_yaw = '1.5708'  # 90도 (북쪽, 복도 안쪽을 향함)

    return LaunchDescription([

        # ── Gz Sim 실행 ──
        ExecuteProcess(
            cmd=[
                'gz', 'sim', '-r', world_file,
            ],
            output='screen',
        ),

        # ── robot_state_publisher ──
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            parameters=[{'robot_description': robot_description}],
            output='screen',
        ),

        # ── 로봇 스폰 ──
        Node(
            package='ros_gz_sim',
            executable='create',
            arguments=[
                '-name', 'hospital_robot',
                '-topic', 'robot_description',
                '-x', spawn_x,
                '-y', spawn_y,
                '-z', spawn_z,
                '-Y', spawn_yaw,
            ],
            output='screen',
        ),

        # ── ros_gz bridge ──
        Node(
            package='ros_gz_bridge',
            executable='parameter_bridge',
            arguments=[
                # cmd_vel: ROS2 → Gz
                '/cmd_vel@geometry_msgs/msg/Twist@gz.msgs.Twist',
                # odom: Gz → ROS2
                '/odom@nav_msgs/msg/Odometry@gz.msgs.Odometry',
                # scan: Gz → ROS2
                '/scan@sensor_msgs/msg/LaserScan@gz.msgs.LaserScan',
                # camera: Gz → ROS2
                '/camera/image_raw@sensor_msgs/msg/Image@gz.msgs.Image',
                '/camera/camera_info@sensor_msgs/msg/CameraInfo@gz.msgs.CameraInfo',
                # tf: Gz → ROS2
                '/tf@tf2_msgs/msg/TFMessage@gz.msgs.Pose_V',
                # joint states
                '/joint_states@sensor_msgs/msg/JointState@gz.msgs.Model',
            ],
            output='screen',
        ),
    ])
