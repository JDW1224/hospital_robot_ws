from setuptools import setup, find_packages
import os
from glob import glob

package_name = 'hospital_robot_poi'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/poi', glob('poi/*.yaml')),
        ('share/' + package_name + '/rviz', glob('rviz/*.rviz')),
    ],
    install_requires=['setuptools', 'pyyaml'],
    zip_safe=True,
    entry_points={
        'console_scripts': [
            'poi_registrar = hospital_robot_poi.poi_registrar_node:main',
        ],
    },
)
