// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hospital_robot_msgs:srv/GetPOIList.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__TRAITS_HPP_
#define HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "hospital_robot_msgs/srv/detail/get_poi_list__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace hospital_robot_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetPOIList_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetPOIList_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetPOIList_Request & msg, bool use_flow_style = false)
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
  const hospital_robot_msgs::srv::GetPOIList_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  hospital_robot_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hospital_robot_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const hospital_robot_msgs::srv::GetPOIList_Request & msg)
{
  return hospital_robot_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<hospital_robot_msgs::srv::GetPOIList_Request>()
{
  return "hospital_robot_msgs::srv::GetPOIList_Request";
}

template<>
inline const char * name<hospital_robot_msgs::srv::GetPOIList_Request>()
{
  return "hospital_robot_msgs/srv/GetPOIList_Request";
}

template<>
struct has_fixed_size<hospital_robot_msgs::srv::GetPOIList_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<hospital_robot_msgs::srv::GetPOIList_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<hospital_robot_msgs::srv::GetPOIList_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace hospital_robot_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetPOIList_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: ids
  {
    if (msg.ids.size() == 0) {
      out << "ids: []";
    } else {
      out << "ids: [";
      size_t pending_items = msg.ids.size();
      for (auto item : msg.ids) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: names
  {
    if (msg.names.size() == 0) {
      out << "names: []";
    } else {
      out << "names: [";
      size_t pending_items = msg.names.size();
      for (auto item : msg.names) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetPOIList_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: ids
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.ids.size() == 0) {
      out << "ids: []\n";
    } else {
      out << "ids:\n";
      for (auto item : msg.ids) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: names
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.names.size() == 0) {
      out << "names: []\n";
    } else {
      out << "names:\n";
      for (auto item : msg.names) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetPOIList_Response & msg, bool use_flow_style = false)
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
  const hospital_robot_msgs::srv::GetPOIList_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  hospital_robot_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hospital_robot_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const hospital_robot_msgs::srv::GetPOIList_Response & msg)
{
  return hospital_robot_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<hospital_robot_msgs::srv::GetPOIList_Response>()
{
  return "hospital_robot_msgs::srv::GetPOIList_Response";
}

template<>
inline const char * name<hospital_robot_msgs::srv::GetPOIList_Response>()
{
  return "hospital_robot_msgs/srv/GetPOIList_Response";
}

template<>
struct has_fixed_size<hospital_robot_msgs::srv::GetPOIList_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<hospital_robot_msgs::srv::GetPOIList_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<hospital_robot_msgs::srv::GetPOIList_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<hospital_robot_msgs::srv::GetPOIList>()
{
  return "hospital_robot_msgs::srv::GetPOIList";
}

template<>
inline const char * name<hospital_robot_msgs::srv::GetPOIList>()
{
  return "hospital_robot_msgs/srv/GetPOIList";
}

template<>
struct has_fixed_size<hospital_robot_msgs::srv::GetPOIList>
  : std::integral_constant<
    bool,
    has_fixed_size<hospital_robot_msgs::srv::GetPOIList_Request>::value &&
    has_fixed_size<hospital_robot_msgs::srv::GetPOIList_Response>::value
  >
{
};

template<>
struct has_bounded_size<hospital_robot_msgs::srv::GetPOIList>
  : std::integral_constant<
    bool,
    has_bounded_size<hospital_robot_msgs::srv::GetPOIList_Request>::value &&
    has_bounded_size<hospital_robot_msgs::srv::GetPOIList_Response>::value
  >
{
};

template<>
struct is_service<hospital_robot_msgs::srv::GetPOIList>
  : std::true_type
{
};

template<>
struct is_service_request<hospital_robot_msgs::srv::GetPOIList_Request>
  : std::true_type
{
};

template<>
struct is_service_response<hospital_robot_msgs::srv::GetPOIList_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__TRAITS_HPP_
