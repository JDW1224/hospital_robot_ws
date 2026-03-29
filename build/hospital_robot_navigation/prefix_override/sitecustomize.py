import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/team9/hostpital_robot_ws/install/hospital_robot_navigation'
