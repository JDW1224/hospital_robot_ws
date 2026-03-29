// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hospital_robot_msgs:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_
#define HOSPITAL_ROBOT_MSGS__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hospital_robot_msgs/msg/detail/robot_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hospital_robot_msgs
{

namespace msg
{

namespace builder
{

class Init_RobotStatus_battery_percent
{
public:
  explicit Init_RobotStatus_battery_percent(::hospital_robot_msgs::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  ::hospital_robot_msgs::msg::RobotStatus battery_percent(::hospital_robot_msgs::msg::RobotStatus::_battery_percent_type arg)
  {
    msg_.battery_percent = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hospital_robot_msgs::msg::RobotStatus msg_;
};

class Init_RobotStatus_current_yaw
{
public:
  explicit Init_RobotStatus_current_yaw(::hospital_robot_msgs::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_battery_percent current_yaw(::hospital_robot_msgs::msg::RobotStatus::_current_yaw_type arg)
  {
    msg_.current_yaw = std::move(arg);
    return Init_RobotStatus_battery_percent(msg_);
  }

private:
  ::hospital_robot_msgs::msg::RobotStatus msg_;
};

class Init_RobotStatus_current_y
{
public:
  explicit Init_RobotStatus_current_y(::hospital_robot_msgs::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_current_yaw current_y(::hospital_robot_msgs::msg::RobotStatus::_current_y_type arg)
  {
    msg_.current_y = std::move(arg);
    return Init_RobotStatus_current_yaw(msg_);
  }

private:
  ::hospital_robot_msgs::msg::RobotStatus msg_;
};

class Init_RobotStatus_current_x
{
public:
  explicit Init_RobotStatus_current_x(::hospital_robot_msgs::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_current_y current_x(::hospital_robot_msgs::msg::RobotStatus::_current_x_type arg)
  {
    msg_.current_x = std::move(arg);
    return Init_RobotStatus_current_y(msg_);
  }

private:
  ::hospital_robot_msgs::msg::RobotStatus msg_;
};

class Init_RobotStatus_current_goal_id
{
public:
  explicit Init_RobotStatus_current_goal_id(::hospital_robot_msgs::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_current_x current_goal_id(::hospital_robot_msgs::msg::RobotStatus::_current_goal_id_type arg)
  {
    msg_.current_goal_id = std::move(arg);
    return Init_RobotStatus_current_x(msg_);
  }

private:
  ::hospital_robot_msgs::msg::RobotStatus msg_;
};

class Init_RobotStatus_estop_state
{
public:
  explicit Init_RobotStatus_estop_state(::hospital_robot_msgs::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_current_goal_id estop_state(::hospital_robot_msgs::msg::RobotStatus::_estop_state_type arg)
  {
    msg_.estop_state = std::move(arg);
    return Init_RobotStatus_current_goal_id(msg_);
  }

private:
  ::hospital_robot_msgs::msg::RobotStatus msg_;
};

class Init_RobotStatus_nav_state
{
public:
  Init_RobotStatus_nav_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotStatus_estop_state nav_state(::hospital_robot_msgs::msg::RobotStatus::_nav_state_type arg)
  {
    msg_.nav_state = std::move(arg);
    return Init_RobotStatus_estop_state(msg_);
  }

private:
  ::hospital_robot_msgs::msg::RobotStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hospital_robot_msgs::msg::RobotStatus>()
{
  return hospital_robot_msgs::msg::builder::Init_RobotStatus_nav_state();
}

}  // namespace hospital_robot_msgs

#endif  // HOSPITAL_ROBOT_MSGS__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_
