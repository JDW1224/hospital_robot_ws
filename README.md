# 병원 안내 로봇 · Hospital Robot

**2026년 6월 · 캡스톤디자인**

병원 복도 환경에서 목적지까지 이동하는 안내 로봇을 위한 ROS 2 프로젝트다. SLAM 기반 지도 작성과 Nav2 주행, 웹·음성 목적지 입력, 사람 감지와 정지 제어를 연결한다.

## 소스에 포함된 기능

- **지도 작성·주행:** SLAM Toolbox, Nav2·AMCL 설정과 Gazebo 병원 복도 월드, URDF 모델.
- **목적지 처리:** YAML 기반 POI 저장, 한국어 목적지 입력 파싱, 경유지 순서와 `NavigateToPose` 액션을 이용한 목표 전송.
- **웹 조작:** FastAPI·WebSocket으로 목적지 선택, 주행 취소, 비상정지 입력과 주행 상태 표시. 브라우저 음성 인식 API를 사용하는 한국어 입력 UI 포함.
- **인지·정지 제어:** YOLO 탐지 결과의 크기·위치·연속 프레임 조건을 이용한 사람 감지와 속도 감속/재출발 제어. 별도 `hospital_robot_safety` 패키지에 라이다 기반 정지 제어 구현도 포함.
- **기초 주행 도구:** 키보드 조작, 오도메트리 기반 직진 거리 시험, 시간 기반 회전 명령 스크립트.

웹 명령은 `/navigate_to_poi`를 거쳐 목표 전송 노드에 전달되며, 상태는 `/nav_state`를 통해 웹으로 반환된다. 인지 런치의 정지 게이트는 `/cmd_vel_nav`를 입력받아 `/cmd_vel_hc`로 출력한다. `hospital_robot_safety`의 별도 구현은 출력 토픽과 감지 조건이 다르다.

## 구성

| 경로 | 내용 |
| --- | --- |
| `src/hospital_robot_bringup` | 통합 런치, SLAM·Nav2 설정, RViz 설정 |
| `src/hospital_robot_description` | URDF, 병원 복도 시뮬레이션 월드 |
| `src/hospital_robot_msgs` | 상태 메시지와 목적지·정지 관련 서비스 정의 |
| `src/hospital_robot_navigation` | Nav2 목표 전송, 경유지 진행, 스캔 프레임 변환 |
| `src/hospital_robot_poi` | POI YAML, 조회·파싱·등록 도구, 기존 테스트 |
| `src/hospital_robot_web` | 웹 서버와 모바일 UI |
| `src/hospital_robot_perception` | YOLO 사람 탐지와 감속 게이트 |
| `src/hospital_robot_safety` | 라이다 조건을 포함한 별도 정지 게이트 |
| `src/sllidar_ros2` | 외부 SLAMTEC 라이다 드라이버·SDK |
| `maps` | 지도 이미지와 지도 설정 |
| 루트 Python 파일 | `drive_im.py`, `turn_90.py`, `wheelchair_teleop.py` |

## 환경과 준비

기준 환경은 **ROS 2 Jazzy**이며, 시뮬레이션 런치는 **Gazebo Sim 8**과 `ros_gz`를 사용한다. 주요 의존성은 `colcon`, `rosdep`, Nav2, SLAM Toolbox, `robot_state_publisher`, `joint_state_publisher`, `xacro`, `laser_filters`, `v4l2_camera`, `cv_bridge`이다. 실제 센서 런치는 `turtlebot3_node`도 사용한다.

Python 의존성은 PyYAML, FastAPI, Uvicorn, OpenCV, Ultralytics YOLO이다. 일부 Python 의존성은 패키지 선언에 빠져 있어 ROS Python 환경에 별도로 설치해야 한다.

Linux·ROS 환경에서 저장소를 소스의 기본 작업공간 경로인 `~/hospital_robot_ws`에 받는다.

```bash
git clone https://github.com/JDW1224/hospital_robot_ws.git ~/hospital_robot_ws
cd ~/hospital_robot_ws
source /opt/ros/jazzy/setup.bash
# rosdep 초기 설정과 패키지 인덱스 갱신을 마친 환경에서 실행
rosdep install --from-paths src --ignore-src -r -y
colcon build --symlink-install
source install/setup.bash
```

실제 하드웨어에서는 `/dev/rplidar`, `/dev/videoCamera` 등의 장치 이름, 시리얼 설정, `odom`·TF 구성과 로봇 인터페이스를 먼저 맞춰야 한다.

## 실행 예시

각 명령은 필요한 의존성을 준비한 뒤, 별도 터미널에서 ROS와 작업공간 설정을 불러와 실행한다.

```bash
# Gazebo 환경에서 SLAM 런치
ros2 launch hospital_robot_bringup slam.launch.py

# 실제 센서 및 저장된 지도를 이용하는 경우
ros2 launch hospital_robot_bringup view_sensors.launch.py
ros2 launch hospital_robot_bringup navigation.launch.py map:="$HOME/hospital_robot_ws/maps/hospital_map.yaml"
ros2 run hospital_robot_navigation goal_sender

# 웹 서버
ros2 launch hospital_robot_web web.launch.py
```

`navigation.launch.py`는 실기기용이다. 지도 좌표와 POI는 `maps/` 및 `src/hospital_robot_poi/poi/destinations.yaml`에서 설정한다.

### 사람 탐지 모델

`best.pt` 가중치는 저장소에 포함되어 있지 않다. 호환되는 학습 모델을 준비하고 경로를 지정한다.

```bash
export HOSPITAL_ROBOT_MODEL="$HOME/hospital_robot_ws/models/best.pt"
ros2 launch hospital_robot_perception perception.launch.py
```

`.env.example`은 설정 예시이며 자동으로 로드되지 않는다. 직접 실행하는 노드에는 ROS `model_path` 파라미터로도 경로를 전달할 수 있다.

### HTTPS 인증서

개인키와 기존 인증서는 공개 저장소에서 제외했다. 웹 서버는 기본적으로 `~/hospital_robot_ws/certs/cert.pem`과 `key.pem`을 찾으며, 둘 다 있으면 HTTPS 8443 포트를 사용하고 없으면 HTTP 8000 포트를 사용한다. 필요한 인증서는 실행 환경에서 별도로 준비한다. 브라우저 음성 입력 지원은 브라우저와 보안 연결 조건에 따라 달라진다.

## 확인된 제약

- Python 구문과 XML 정적 검사를 통과했다. ROS 빌드·시뮬레이션·실기기 주행·추론은 이번 정리 과정에서 재검증하지 않았다.
- 기존 POI 테스트 일부는 현재 구현에 없는 이전 API를 참조하므로 정리가 필요하다.
- 모델 가중치와 실행용 인증서·개인키는 별도 준비가 필요하다. Python 패키지 버전과 Jetson/CUDA 조합은 고정되어 있지 않다.

## 외부 코드와 라이선스

`src/sllidar_ros2`는 SLAMTEC의 외부 드라이버다. 라이선스와 저작권 표기는 원본을 유지했다. 출처·기록된 리비전은 [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md), 나머지 패키지의 라이선스 선언은 각 `package.xml`과 `setup.py`를 참조한다.
