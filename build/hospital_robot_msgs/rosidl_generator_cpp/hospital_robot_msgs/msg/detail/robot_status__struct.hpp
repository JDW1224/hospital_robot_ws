// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hospital_robot_msgs:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__MSG__DETAIL__ROBOT_STATUS__STRUCT_HPP_
#define HOSPITAL_ROBOT_MSGS__MSG__DETAIL__ROBOT_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hospital_robot_msgs__msg__RobotStatus __attribute__((deprecated))
#else
# define DEPRECATED__hospital_robot_msgs__msg__RobotStatus __declspec(deprecated)
#endif

namespace hospital_robot_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RobotStatus_
{
  using Type = RobotStatus_<ContainerAllocator>;

  explicit RobotStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->nav_state = "";
      this->estop_state = "";
      this->current_goal_id = "";
      this->current_x = 0.0;
      this->current_y = 0.0;
      this->current_yaw = 0.0;
      this->battery_percent = 0.0;
    }
  }

  explicit RobotStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : nav_state(_alloc),
    estop_state(_alloc),
    current_goal_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->nav_state = "";
      this->estop_state = "";
      this->current_goal_id = "";
      this->current_x = 0.0;
      this->current_y = 0.0;
      this->current_yaw = 0.0;
      this->battery_percent = 0.0;
    }
  }

  // field types and members
  using _nav_state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _nav_state_type nav_state;
  using _estop_state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _estop_state_type estop_state;
  using _current_goal_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _current_goal_id_type current_goal_id;
  using _current_x_type =
    double;
  _current_x_type current_x;
  using _current_y_type =
    double;
  _current_y_type current_y;
  using _current_yaw_type =
    double;
  _current_yaw_type current_yaw;
  using _battery_percent_type =
    double;
  _battery_percent_type battery_percent;

  // setters for named parameter idiom
  Type & set__nav_state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->nav_state = _arg;
    return *this;
  }
  Type & set__estop_state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->estop_state = _arg;
    return *this;
  }
  Type & set__current_goal_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->current_goal_id = _arg;
    return *this;
  }
  Type & set__current_x(
    const double & _arg)
  {
    this->current_x = _arg;
    return *this;
  }
  Type & set__current_y(
    const double & _arg)
  {
    this->current_y = _arg;
    return *this;
  }
  Type & set__current_yaw(
    const double & _arg)
  {
    this->current_yaw = _arg;
    return *this;
  }
  Type & set__battery_percent(
    const double & _arg)
  {
    this->battery_percent = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hospital_robot_msgs::msg::RobotStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const hospital_robot_msgs::msg::RobotStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hospital_robot_msgs::msg::RobotStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hospital_robot_msgs::msg::RobotStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hospital_robot_msgs::msg::RobotStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hospital_robot_msgs::msg::RobotStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hospital_robot_msgs::msg::RobotStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hospital_robot_msgs::msg::RobotStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hospital_robot_msgs::msg::RobotStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hospital_robot_msgs::msg::RobotStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hospital_robot_msgs__msg__RobotStatus
    std::shared_ptr<hospital_robot_msgs::msg::RobotStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hospital_robot_msgs__msg__RobotStatus
    std::shared_ptr<hospital_robot_msgs::msg::RobotStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotStatus_ & other) const
  {
    if (this->nav_state != other.nav_state) {
      return false;
    }
    if (this->estop_state != other.estop_state) {
      return false;
    }
    if (this->current_goal_id != other.current_goal_id) {
      return false;
    }
    if (this->current_x != other.current_x) {
      return false;
    }
    if (this->current_y != other.current_y) {
      return false;
    }
    if (this->current_yaw != other.current_yaw) {
      return false;
    }
    if (this->battery_percent != other.battery_percent) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotStatus_

// alias to use template instance with default allocator
using RobotStatus =
  hospital_robot_msgs::msg::RobotStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace hospital_robot_msgs

#endif  // HOSPITAL_ROBOT_MSGS__MSG__DETAIL__ROBOT_STATUS__STRUCT_HPP_
