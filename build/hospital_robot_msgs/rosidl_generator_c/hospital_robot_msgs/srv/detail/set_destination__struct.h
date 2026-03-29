// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hospital_robot_msgs:srv/SetDestination.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__SRV__DETAIL__SET_DESTINATION__STRUCT_H_
#define HOSPITAL_ROBOT_MSGS__SRV__DETAIL__SET_DESTINATION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'destination_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetDestination in the package hospital_robot_msgs.
typedef struct hospital_robot_msgs__srv__SetDestination_Request
{
  /// "301", "entrance", "elevator" 등
  rosidl_runtime_c__String destination_id;
} hospital_robot_msgs__srv__SetDestination_Request;

// Struct for a sequence of hospital_robot_msgs__srv__SetDestination_Request.
typedef struct hospital_robot_msgs__srv__SetDestination_Request__Sequence
{
  hospital_robot_msgs__srv__SetDestination_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hospital_robot_msgs__srv__SetDestination_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetDestination in the package hospital_robot_msgs.
typedef struct hospital_robot_msgs__srv__SetDestination_Response
{
  /// 성공 여부
  bool success;
  /// 실패 시 사유
  rosidl_runtime_c__String message;
  /// 목표 좌표 x
  double goal_x;
  /// 목표 좌표 y
  double goal_y;
  /// 목표 방향
  double goal_yaw;
} hospital_robot_msgs__srv__SetDestination_Response;

// Struct for a sequence of hospital_robot_msgs__srv__SetDestination_Response.
typedef struct hospital_robot_msgs__srv__SetDestination_Response__Sequence
{
  hospital_robot_msgs__srv__SetDestination_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hospital_robot_msgs__srv__SetDestination_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HOSPITAL_ROBOT_MSGS__SRV__DETAIL__SET_DESTINATION__STRUCT_H_
