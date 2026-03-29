// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hospital_robot_msgs:srv/SetDestination.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__SRV__DETAIL__SET_DESTINATION__BUILDER_HPP_
#define HOSPITAL_ROBOT_MSGS__SRV__DETAIL__SET_DESTINATION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hospital_robot_msgs/srv/detail/set_destination__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hospital_robot_msgs
{

namespace srv
{

namespace builder
{

class Init_SetDestination_Request_destination_id
{
public:
  Init_SetDestination_Request_destination_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::hospital_robot_msgs::srv::SetDestination_Request destination_id(::hospital_robot_msgs::srv::SetDestination_Request::_destination_id_type arg)
  {
    msg_.destination_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hospital_robot_msgs::srv::SetDestination_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::hospital_robot_msgs::srv::SetDestination_Request>()
{
  return hospital_robot_msgs::srv::builder::Init_SetDestination_Request_destination_id();
}

}  // namespace hospital_robot_msgs


namespace hospital_robot_msgs
{

namespace srv
{

namespace builder
{

class Init_SetDestination_Response_goal_yaw
{
public:
  explicit Init_SetDestination_Response_goal_yaw(::hospital_robot_msgs::srv::SetDestination_Response & msg)
  : msg_(msg)
  {}
  ::hospital_robot_msgs::srv::SetDestination_Response goal_yaw(::hospital_robot_msgs::srv::SetDestination_Response::_goal_yaw_type arg)
  {
    msg_.goal_yaw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hospital_robot_msgs::srv::SetDestination_Response msg_;
};

class Init_SetDestination_Response_goal_y
{
public:
  explicit Init_SetDestination_Response_goal_y(::hospital_robot_msgs::srv::SetDestination_Response & msg)
  : msg_(msg)
  {}
  Init_SetDestination_Response_goal_yaw goal_y(::hospital_robot_msgs::srv::SetDestination_Response::_goal_y_type arg)
  {
    msg_.goal_y = std::move(arg);
    return Init_SetDestination_Response_goal_yaw(msg_);
  }

private:
  ::hospital_robot_msgs::srv::SetDestination_Response msg_;
};

class Init_SetDestination_Response_goal_x
{
public:
  explicit Init_SetDestination_Response_goal_x(::hospital_robot_msgs::srv::SetDestination_Response & msg)
  : msg_(msg)
  {}
  Init_SetDestination_Response_goal_y goal_x(::hospital_robot_msgs::srv::SetDestination_Response::_goal_x_type arg)
  {
    msg_.goal_x = std::move(arg);
    return Init_SetDestination_Response_goal_y(msg_);
  }

private:
  ::hospital_robot_msgs::srv::SetDestination_Response msg_;
};

class Init_SetDestination_Response_message
{
public:
  explicit Init_SetDestination_Response_message(::hospital_robot_msgs::srv::SetDestination_Response & msg)
  : msg_(msg)
  {}
  Init_SetDestination_Response_goal_x message(::hospital_robot_msgs::srv::SetDestination_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_SetDestination_Response_goal_x(msg_);
  }

private:
  ::hospital_robot_msgs::srv::SetDestination_Response msg_;
};

class Init_SetDestination_Response_success
{
public:
  Init_SetDestination_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetDestination_Response_message success(::hospital_robot_msgs::srv::SetDestination_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetDestination_Response_message(msg_);
  }

private:
  ::hospital_robot_msgs::srv::SetDestination_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::hospital_robot_msgs::srv::SetDestination_Response>()
{
  return hospital_robot_msgs::srv::builder::Init_SetDestination_Response_success();
}

}  // namespace hospital_robot_msgs

#endif  // HOSPITAL_ROBOT_MSGS__SRV__DETAIL__SET_DESTINATION__BUILDER_HPP_
