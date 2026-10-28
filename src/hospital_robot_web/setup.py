from setuptools import setup, find_packages
from glob import glob

package_name = 'hospital_robot_web'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', glob('launch/*.py')),
        ('share/' + package_name + '/web', glob('web/*')),
    ],
    install_requires=['setuptools', 'fastapi', 'uvicorn'],
    zip_safe=True,
    entry_points={
        'console_scripts': [
            'web_server = hospital_robot_web.web_server_node:main',
            'fake_goal_sender = hospital_robot_web.fake_goal_sender:main',
        ],
    },
)
