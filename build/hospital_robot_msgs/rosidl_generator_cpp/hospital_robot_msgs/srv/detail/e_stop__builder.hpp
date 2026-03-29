// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hospital_robot_msgs:srv/EStop.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__SRV__DETAIL__E_STOP__BUILDER_HPP_
#define HOSPITAL_ROBOT_MSGS__SRV__DETAIL__E_STOP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hospital_robot_msgs/srv/detail/e_stop__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hospital_robot_msgs
{

namespace srv
{

namespace builder
{

class Init_EStop_Request_activate
{
public:
  Init_EStop_Request_activate()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::hospital_robot_msgs::srv::EStop_Request activate(::hospital_robot_msgs::srv::EStop_Request::_activate_type arg)
  {
    msg_.activate = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hospital_robot_msgs::srv::EStop_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::hospital_robot_msgs::srv::EStop_Request>()
{
  return hospital_robot_msgs::srv::builder::Init_EStop_Request_activate();
}

}  // namespace hospital_robot_msgs


namespace hospital_robot_msgs
{

namespace srv
{

namespace builder
{

class Init_EStop_Response_state
{
public:
  explicit Init_EStop_Response_state(::hospital_robot_msgs::srv::EStop_Response & msg)
  : msg_(msg)
  {}
  ::hospital_robot_msgs::srv::EStop_Response state(::hospital_robot_msgs::srv::EStop_Response::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hospital_robot_msgs::srv::EStop_Response msg_;
};

class Init_EStop_Response_success
{
public:
  Init_EStop_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EStop_Response_state success(::hospital_robot_msgs::srv::EStop_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_EStop_Response_state(msg_);
  }

private:
  ::hospital_robot_msgs::srv::EStop_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::hospital_robot_msgs::srv::EStop_Response>()
{
  return hospital_robot_msgs::srv::builder::Init_EStop_Response_success();
}

}  // namespace hospital_robot_msgs

#endif  // HOSPITAL_ROBOT_MSGS__SRV__DETAIL__E_STOP__BUILDER_HPP_
