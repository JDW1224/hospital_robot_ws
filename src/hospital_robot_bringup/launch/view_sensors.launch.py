import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():

    pkg_description = get_package_share_directory('hospital_robot_description')
    pkg_bringup = get_package_share_directory('hospital_robot_bringup')
    xacro_file = os.path.join(pkg_description, 'urdf', 'robot.urdf.xacro')
    scan_filter_config = os.path.join(pkg_bringup, 'config', 'scan_filter.yaml')
    
    robot_description = ParameterValue(Command(['xacro ', xacro_file]), value_type=str)

    rsp_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description': robot_description, 'use_sim_time': False}],
        output='screen'
    )

    jsp_node = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        parameters=[{'use_sim_time': False}],
        output='screen'
    )

    # 라이다 (원본 /scan_raw로 발행)
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
        remappings=[('/scan', '/scan_raw')],   # ⭐ /scan → /scan_raw로 변경
        output='screen'
    )

    # ⭐ 스캔 필터 노드 (라이다 뒤쪽 90도 제거)
    scan_filter_node = Node(
        package='laser_filters',
        executable='scan_to_scan_filter_chain',
        parameters=[scan_filter_config],
        remappings=[
            ('scan', '/scan_raw'),       # 입력: 원본
            ('scan_filtered', '/scan'),  # 출력: 필터링된 scan
        ],
        output='screen'
    )

    camera_node = Node(
        package='v4l2_camera',
        executable='v4l2_camera_node',
        name='camera_node',
        parameters=[{
            'video_device': '/dev/videoCamera',
            'image_size': [640, 480],
            'camera_frame_id': 'camera_link',
            'use_sim_time': False
        }],
        output='screen'
    )

    TURTLEBOT3_MODEL = os.environ.get('TURTLEBOT3_MODEL', 'waffle_pi')
    tb3_param_dir = os.path.join(
        get_package_share_directory('turtlebot3_bringup'),
        'param',
        'humble',
        TURTLEBOT3_MODEL + '.yaml'
    )
    turtlebot_node = Node(
        package='turtlebot3_node',
        executable='turtlebot3_ros',
        parameters=[tb3_param_dir, {'namespace': ''}],
        arguments=['-i', os.environ.get('OPENCR_PORT', '/dev/ttyOpenCR')],
        remappings=[('/cmd_vel', '/cmd_vel_hc')],
        output='screen'
    )

    return LaunchDescription([
        rsp_node,
        jsp_node,
        lidar_node,
        scan_filter_node,   # ⭐ 추가
        camera_node,
        turtlebot_node,
    ])