#!/usr/bin/env python3
"""
Scan frame_id 리맵 노드
Gz Sim 8이 발행하는 scan frame_id (hospital_robot/base_footprint/lidar)를
표준 frame_id (lidar_link)로 변환
"""
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, DurabilityPolicy
from sensor_msgs.msg import LaserScan


class ScanFrameRemapper(Node):
    def __init__(self):
        super().__init__('scan_frame_remapper')

        self.declare_parameter('input_topic', '/scan')
        self.declare_parameter('output_topic', '/scan_fixed')
        self.declare_parameter('target_frame', 'lidar_link')

        input_topic = self.get_parameter('input_topic').get_parameter_value().string_value
        output_topic = self.get_parameter('output_topic').get_parameter_value().string_value
        self.target_frame = self.get_parameter('target_frame').get_parameter_value().string_value

        qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.VOLATILE,
            depth=5,
        )

        self.sub = self.create_subscription(LaserScan, input_topic, self.callback, qos)
        self.pub = self.create_publisher(LaserScan, output_topic, qos)
        self.get_logger().info(
            f'Remapping: {input_topic} -> {output_topic} (frame: {self.target_frame})'
        )

    def callback(self, msg: LaserScan):
        msg.header.frame_id = self.target_frame
        self.pub.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = ScanFrameRemapper()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
