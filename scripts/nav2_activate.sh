#!/bin/bash
# nav2_activate.sh
# navigation.launch.py 실행 후 이 스크립트를 별도 터미널에서 실행
# 모든 Nav2 노드를 자동 활성화하고 cmd_vel relay 시작

set -e

echo "⏳ Nav2 노드 대기중..."

# 노드가 뜰 때까지 대기
wait_for_node() {
    local node=$1
    local timeout=30
    local count=0
    while ! ros2 node list 2>/dev/null | grep -q "$node"; do
        sleep 1
        count=$((count + 1))
        if [ $count -ge $timeout ]; then
            echo "❌ 타임아웃: $node 노드를 찾을 수 없음"
            exit 1
        fi
    done
    echo "  ✓ $node 발견"
}

wait_for_node "/bt_navigator"
wait_for_node "/controller_server"
wait_for_node "/planner_server"
wait_for_node "/map_server"
wait_for_node "/amcl"

# lifecycle_manager_localization이 map_server + amcl 올릴 시간 대기
echo "⏳ Localization 활성화 대기 (5초)..."
sleep 5

# costmap 활성화
echo "🔧 Costmap 활성화..."
ros2 lifecycle set /local_costmap/local_costmap activate 2>/dev/null || true
ros2 lifecycle set /global_costmap/global_costmap activate 2>/dev/null || true

# Nav2 서버 활성화
echo "🔧 Nav2 서버 활성화..."
ros2 lifecycle set /controller_server activate 2>/dev/null || true
ros2 lifecycle set /smoother_server activate 2>/dev/null || true
ros2 lifecycle set /planner_server activate 2>/dev/null || true
ros2 lifecycle set /behavior_server activate 2>/dev/null || true
ros2 lifecycle set /velocity_smoother activate 2>/dev/null || true

# bt_navigator (unconfigured → configure → activate)
echo "🔧 BT Navigator 활성화..."
ros2 lifecycle set /bt_navigator configure 2>/dev/null || true
sleep 1
ros2 lifecycle set /bt_navigator activate 2>/dev/null || true

# relay 시작 (collision_monitor 우회)
echo "🔧 cmd_vel relay 시작..."
ros2 run topic_tools relay /cmd_vel_smoothed /cmd_vel &
RELAY_PID=$!

echo ""
echo "✅ Nav2 전체 활성화 완료!"
echo "   RViz에서 2D Goal Pose 찍으면 바로 움직입니다."
echo "   종료: Ctrl+C"
echo ""

# relay 프로세스 유지
wait $RELAY_PID
