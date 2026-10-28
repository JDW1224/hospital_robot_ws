from setuptools import setup
import os
from glob import glob

package_name = 'hospital_robot_perception'

setup(
    name=package_name,
    version='1.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='team9',
    maintainer_email='team9@todo.todo',
    description='YOLO human detection + smooth safety stop gate',
    license='MIT',
    entry_points={
        'console_scripts': [
            'yolo_detector = hospital_robot_perception.yolo_detector_node:main',
            'safety_gate = hospital_robot_perception.safety_gate_node:main',
        ],
    },
)
