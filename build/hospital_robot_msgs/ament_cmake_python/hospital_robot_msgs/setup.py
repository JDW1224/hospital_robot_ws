from setuptools import find_packages
from setuptools import setup

setup(
    name='hospital_robot_msgs',
    version='0.1.0',
    packages=find_packages(
        include=('hospital_robot_msgs', 'hospital_robot_msgs.*')),
)
