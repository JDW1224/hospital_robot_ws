// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hospital_robot_msgs:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__MSG__DETAIL__ROBOT_STATUS__TRAITS_HPP_
#define HOSPITAL_ROBOT_MSGS__MSG__DETAIL__ROBOT_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "hospital_robot_msgs/msg/detail/robot_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace hospital_robot_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const RobotStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: nav_state
  {
    out << "nav_state: ";
    rosidl_generator_traits::value_to_yaml(msg.nav_state, out);
    out << ", ";
  }

  // member: estop_state
  {
    out << "estop_state: ";
    rosidl_generator_traits::value_to_yaml(msg.estop_state, out);
    out << ", ";
  }

  // member: current_goal_id
  {
    out << "current_goal_id: ";
    rosidl_generator_traits::value_to_yaml(msg.current_goal_id, out);
    out << ", ";
  }

  // member: current_x
  {
    out << "current_x: ";
    rosidl_generator_traits::value_to_yaml(msg.current_x, out);
    out << ", ";
  }

  // member: current_y
  {
    out << "current_y: ";
    rosidl_generator_traits::value_to_yaml(msg.current_y, out);
    out << ", ";
  }

  // member: current_yaw
  {
    out << "current_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.current_yaw, out);
    out << ", ";
  }

  // member: battery_percent
  {
    out << "battery_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_percent, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RobotStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: nav_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "nav_state: ";
    rosidl_generator_traits::value_to_yaml(msg.nav_state, out);
    out << "\n";
  }

  // member: estop_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "estop_state: ";
    rosidl_generator_traits::value_to_yaml(msg.estop_state, out);
    out << "\n";
  }

  // member: current_goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_goal_id: ";
    rosidl_generator_traits::value_to_yaml(msg.current_goal_id, out);
    out << "\n";
  }

  // member: current_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_x: ";
    rosidl_generator_traits::value_to_yaml(msg.current_x, out);
    out << "\n";
  }

  // member: current_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_y: ";
    rosidl_generator_traits::value_to_yaml(msg.current_y, out);
    out << "\n";
  }

  // member: current_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.current_yaw, out);
    out << "\n";
  }

  // member: battery_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_percent, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RobotStatus & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace hospital_robot_msgs

namespace rosidl_generator_traits
{

[[deprecated("use hospital_robot_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hospital_robot_msgs::msg::RobotStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  hospital_robot_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hospital_robot_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const hospital_robot_msgs::msg::RobotStatus & msg)
{
  return hospital_robot_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<hospital_robot_msgs::msg::RobotStatus>()
{
  return "hospital_robot_msgs::msg::RobotStatus";
}

template<>
inline const char * name<hospital_robot_msgs::msg::RobotStatus>()
{
  return "hospital_robot_msgs/msg/RobotStatus";
}

template<>
struct has_fixed_size<hospital_robot_msgs::msg::RobotStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<hospital_robot_msgs::msg::RobotStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<hospital_robot_msgs::msg::RobotStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // HOSPITAL_ROBOT_MSGS__MSG__DETAIL__ROBOT_STATUS__TRAITS_HPP_
