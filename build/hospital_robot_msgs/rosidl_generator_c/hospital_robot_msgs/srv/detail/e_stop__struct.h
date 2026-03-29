// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hospital_robot_msgs:srv/EStop.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__SRV__DETAIL__E_STOP__STRUCT_H_
#define HOSPITAL_ROBOT_MSGS__SRV__DETAIL__E_STOP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/EStop in the package hospital_robot_msgs.
typedef struct hospital_robot_msgs__srv__EStop_Request
{
  /// true: E-Stop 발동 / false: 해제
  bool activate;
} hospital_robot_msgs__srv__EStop_Request;

// Struct for a sequence of hospital_robot_msgs__srv__EStop_Request.
typedef struct hospital_robot_msgs__srv__EStop_Request__Sequence
{
  hospital_robot_msgs__srv__EStop_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hospital_robot_msgs__srv__EStop_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'state'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/EStop in the package hospital_robot_msgs.
typedef struct hospital_robot_msgs__srv__EStop_Response
{
  /// 성공 여부
  bool success;
  /// 현재 상태 (NORMAL / ESTOP)
  rosidl_runtime_c__String state;
} hospital_robot_msgs__srv__EStop_Response;

// Struct for a sequence of hospital_robot_msgs__srv__EStop_Response.
typedef struct hospital_robot_msgs__srv__EStop_Response__Sequence
{
  hospital_robot_msgs__srv__EStop_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hospital_robot_msgs__srv__EStop_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HOSPITAL_ROBOT_MSGS__SRV__DETAIL__E_STOP__STRUCT_H_
