// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hospital_robot_msgs:srv/SetDestination.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__SRV__DETAIL__SET_DESTINATION__TRAITS_HPP_
#define HOSPITAL_ROBOT_MSGS__SRV__DETAIL__SET_DESTINATION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "hospital_robot_msgs/srv/detail/set_destination__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace hospital_robot_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetDestination_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: destination_id
  {
    out << "destination_id: ";
    rosidl_generator_traits::value_to_yaml(msg.destination_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetDestination_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: destination_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "destination_id: ";
    rosidl_generator_traits::value_to_yaml(msg.destination_id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetDestination_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace hospital_robot_msgs

namespace rosidl_generator_traits
{

[[deprecated("use hospital_robot_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hospital_robot_msgs::srv::SetDestination_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  hospital_robot_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hospital_robot_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const hospital_robot_msgs::srv::SetDestination_Request & msg)
{
  return hospital_robot_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<hospital_robot_msgs::srv::SetDestination_Request>()
{
  return "hospital_robot_msgs::srv::SetDestination_Request";
}

template<>
inline const char * name<hospital_robot_msgs::srv::SetDestination_Request>()
{
  return "hospital_robot_msgs/srv/SetDestination_Request";
}

template<>
struct has_fixed_size<hospital_robot_msgs::srv::SetDestination_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<hospital_robot_msgs::srv::SetDestination_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<hospital_robot_msgs::srv::SetDestination_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace hospital_robot_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetDestination_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: goal_x
  {
    out << "goal_x: ";
    rosidl_generator_traits::value_to_yaml(msg.goal_x, out);
    out << ", ";
  }

  // member: goal_y
  {
    out << "goal_y: ";
    rosidl_generator_traits::value_to_yaml(msg.goal_y, out);
    out << ", ";
  }

  // member: goal_yaw
  {
    out << "goal_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.goal_yaw, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetDestination_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }

  // member: goal_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_x: ";
    rosidl_generator_traits::value_to_yaml(msg.goal_x, out);
    out << "\n";
  }

  // member: goal_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_y: ";
    rosidl_generator_traits::value_to_yaml(msg.goal_y, out);
    out << "\n";
  }

  // member: goal_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.goal_yaw, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetDestination_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace hospital_robot_msgs

namespace rosidl_generator_traits
{

[[deprecated("use hospital_robot_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hospital_robot_msgs::srv::SetDestination_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  hospital_robot_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hospital_robot_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const hospital_robot_msgs::srv::SetDestination_Response & msg)
{
  return hospital_robot_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<hospital_robot_msgs::srv::SetDestination_Response>()
{
  return "hospital_robot_msgs::srv::SetDestination_Response";
}

template<>
inline const char * name<hospital_robot_msgs::srv::SetDestination_Response>()
{
  return "hospital_robot_msgs/srv/SetDestination_Response";
}

template<>
struct has_fixed_size<hospital_robot_msgs::srv::SetDestination_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<hospital_robot_msgs::srv::SetDestination_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<hospital_robot_msgs::srv::SetDestination_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<hospital_robot_msgs::srv::SetDestination>()
{
  return "hospital_robot_msgs::srv::SetDestination";
}

template<>
inline const char * name<hospital_robot_msgs::srv::SetDestination>()
{
  return "hospital_robot_msgs/srv/SetDestination";
}

template<>
struct has_fixed_size<hospital_robot_msgs::srv::SetDestination>
  : std::integral_constant<
    bool,
    has_fixed_size<hospital_robot_msgs::srv::SetDestination_Request>::value &&
    has_fixed_size<hospital_robot_msgs::srv::SetDestination_Response>::value
  >
{
};

template<>
struct has_bounded_size<hospital_robot_msgs::srv::SetDestination>
  : std::integral_constant<
    bool,
    has_bounded_size<hospital_robot_msgs::srv::SetDestination_Request>::value &&
    has_bounded_size<hospital_robot_msgs::srv::SetDestination_Response>::value
  >
{
};

template<>
struct is_service<hospital_robot_msgs::srv::SetDestination>
  : std::true_type
{
};

template<>
struct is_service_request<hospital_robot_msgs::srv::SetDestination_Request>
  : std::true_type
{
};

template<>
struct is_service_response<hospital_robot_msgs::srv::SetDestination_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // HOSPITAL_ROBOT_MSGS__SRV__DETAIL__SET_DESTINATION__TRAITS_HPP_
