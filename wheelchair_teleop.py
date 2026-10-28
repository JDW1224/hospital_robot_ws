import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist  # TwistStamped가 아닌 Twist를 가져옵니다.
import sys
import select
import termios
import tty
import threading

class WheelchairTeleop(Node):
    def __init__(self):
        super().__init__('wheelchair_teleop')
        # 토픽 타입을 Twist로 고정합니다.
        self.publisher_ = self.create_publisher(Twist, '/cmd_vel_hc', 10)
        self.timer = self.create_timer(0.1, self.timer_callback) # 10Hz
        self.target_linear = 0.0
        self.target_angular = 0.0
        self.settings = termios.tcgetattr(sys.stdin)
        
    def timer_callback(self):
        # 🌟 에러 발생 지점 수정: TwistStamped() 대신 Twist() 사용
        twist = Twist() 
        twist.linear.x = self.target_linear
        twist.angular.z = self.target_angular
        self.publisher_.publish(twist)

    def stop_robot(self):
        twist = Twist()
        self.publisher_.publish(twist)

def getKey(settings):
    tty.setraw(sys.stdin.fileno())
    select.select([sys.stdin], [], [], 0.1)
    key = sys.stdin.read(1)
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key

def main(args=None):
    rclpy.init(args=args)
    node = WheelchairTeleop()
    
    # 별도 스레드에서 spin 실행 (키 입력을 동시에 받기 위함)
    spin_thread = threading.Thread(target=rclpy.spin, args=(node,), daemon=True)
    spin_thread.start()
    
    print("🏥 로봇 조종 시작: w(전진), x(후진), a(좌), d(우), s(정지)")
    
    try:
        while rclpy.ok():
            key = getKey(node.settings)
            if key == 'w': node.target_linear += 0.05
            elif key == 'x': node.target_linear -= 0.05
            elif key == 'a': node.target_angular += 0.1
            elif key == 'd': node.target_angular -= 0.1
            elif key == 's':
                node.target_linear = 0.0
                node.target_angular = 0.0
            elif key == '\x03': # CTRL-C
                break
            
            if key in ['w', 'x', 'a', 'd', 's']:
                print(f"\r현재 속도: 직진 {node.target_linear:.2f}, 회전 {node.target_angular:.2f}  ", end='')

    except Exception as e:
        print(f"\n에러 발생: {e}")
    finally:
        node.stop_robot()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
