// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hospital_robot_msgs:srv/EStop.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__SRV__DETAIL__E_STOP__TRAITS_HPP_
#define HOSPITAL_ROBOT_MSGS__SRV__DETAIL__E_STOP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "hospital_robot_msgs/srv/detail/e_stop__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace hospital_robot_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const EStop_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: activate
  {
    out << "activate: ";
    rosidl_generator_traits::value_to_yaml(msg.activate, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EStop_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: activate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "activate: ";
    rosidl_generator_traits::value_to_yaml(msg.activate, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EStop_Request & msg, bool use_flow_style = false)
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
  const hospital_robot_msgs::srv::EStop_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  hospital_robot_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hospital_robot_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const hospital_robot_msgs::srv::EStop_Request & msg)
{
  return hospital_robot_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<hospital_robot_msgs::srv::EStop_Request>()
{
  return "hospital_robot_msgs::srv::EStop_Request";
}

template<>
inline const char * name<hospital_robot_msgs::srv::EStop_Request>()
{
  return "hospital_robot_msgs/srv/EStop_Request";
}

template<>
struct has_fixed_size<hospital_robot_msgs::srv::EStop_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<hospital_robot_msgs::srv::EStop_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<hospital_robot_msgs::srv::EStop_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace hospital_robot_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const EStop_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EStop_Response & msg,
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

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EStop_Response & msg, bool use_flow_style = false)
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
  const hospital_robot_msgs::srv::EStop_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  hospital_robot_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hospital_robot_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const hospital_robot_msgs::srv::EStop_Response & msg)
{
  return hospital_robot_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<hospital_robot_msgs::srv::EStop_Response>()
{
  return "hospital_robot_msgs::srv::EStop_Response";
}

template<>
inline const char * name<hospital_robot_msgs::srv::EStop_Response>()
{
  return "hospital_robot_msgs/srv/EStop_Response";
}

template<>
struct has_fixed_size<hospital_robot_msgs::srv::EStop_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<hospital_robot_msgs::srv::EStop_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<hospital_robot_msgs::srv::EStop_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<hospital_robot_msgs::srv::EStop>()
{
  return "hospital_robot_msgs::srv::EStop";
}

template<>
inline const char * name<hospital_robot_msgs::srv::EStop>()
{
  return "hospital_robot_msgs/srv/EStop";
}

template<>
struct has_fixed_size<hospital_robot_msgs::srv::EStop>
  : std::integral_constant<
    bool,
    has_fixed_size<hospital_robot_msgs::srv::EStop_Request>::value &&
    has_fixed_size<hospital_robot_msgs::srv::EStop_Response>::value
  >
{
};

template<>
struct has_bounded_size<hospital_robot_msgs::srv::EStop>
  : std::integral_constant<
    bool,
    has_bounded_size<hospital_robot_msgs::srv::EStop_Request>::value &&
    has_bounded_size<hospital_robot_msgs::srv::EStop_Response>::value
  >
{
};

template<>
struct is_service<hospital_robot_msgs::srv::EStop>
  : std::true_type
{
};

template<>
struct is_service_request<hospital_robot_msgs::srv::EStop_Request>
  : std::true_type
{
};

template<>
struct is_service_response<hospital_robot_msgs::srv::EStop_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // HOSPITAL_ROBOT_MSGS__SRV__DETAIL__E_STOP__TRAITS_HPP_
