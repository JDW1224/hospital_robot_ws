// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hospital_robot_msgs:srv/GetPOIList.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__BUILDER_HPP_
#define HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hospital_robot_msgs/srv/detail/get_poi_list__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hospital_robot_msgs
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::hospital_robot_msgs::srv::GetPOIList_Request>()
{
  return ::hospital_robot_msgs::srv::GetPOIList_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace hospital_robot_msgs


namespace hospital_robot_msgs
{

namespace srv
{

namespace builder
{

class Init_GetPOIList_Response_names
{
public:
  explicit Init_GetPOIList_Response_names(::hospital_robot_msgs::srv::GetPOIList_Response & msg)
  : msg_(msg)
  {}
  ::hospital_robot_msgs::srv::GetPOIList_Response names(::hospital_robot_msgs::srv::GetPOIList_Response::_names_type arg)
  {
    msg_.names = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hospital_robot_msgs::srv::GetPOIList_Response msg_;
};

class Init_GetPOIList_Response_ids
{
public:
  Init_GetPOIList_Response_ids()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetPOIList_Response_names ids(::hospital_robot_msgs::srv::GetPOIList_Response::_ids_type arg)
  {
    msg_.ids = std::move(arg);
    return Init_GetPOIList_Response_names(msg_);
  }

private:
  ::hospital_robot_msgs::srv::GetPOIList_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::hospital_robot_msgs::srv::GetPOIList_Response>()
{
  return hospital_robot_msgs::srv::builder::Init_GetPOIList_Response_ids();
}

}  // namespace hospital_robot_msgs

#endif  // HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__BUILDER_HPP_
