from setuptools import setup, find_packages
package_name = 'hospital_robot_navigation'
setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
        entry_points={
        'console_scripts': [
            'scan_frame_remapper = hospital_robot_navigation.scan_frame_remapper:main',
            'goal_sender = hospital_robot_navigation.goal_sender:main',
        ],
    },
)
