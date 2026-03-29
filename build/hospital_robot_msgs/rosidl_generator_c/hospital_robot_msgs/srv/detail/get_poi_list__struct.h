// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hospital_robot_msgs:srv/GetPOIList.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__STRUCT_H_
#define HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetPOIList in the package hospital_robot_msgs.
typedef struct hospital_robot_msgs__srv__GetPOIList_Request
{
  uint8_t structure_needs_at_least_one_member;
} hospital_robot_msgs__srv__GetPOIList_Request;

// Struct for a sequence of hospital_robot_msgs__srv__GetPOIList_Request.
typedef struct hospital_robot_msgs__srv__GetPOIList_Request__Sequence
{
  hospital_robot_msgs__srv__GetPOIList_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hospital_robot_msgs__srv__GetPOIList_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'ids'
// Member 'names'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetPOIList in the package hospital_robot_msgs.
typedef struct hospital_robot_msgs__srv__GetPOIList_Response
{
  /// 목적지 ID 배열
  rosidl_runtime_c__String__Sequence ids;
  /// 목적지 이름 배열
  rosidl_runtime_c__String__Sequence names;
} hospital_robot_msgs__srv__GetPOIList_Response;

// Struct for a sequence of hospital_robot_msgs__srv__GetPOIList_Response.
typedef struct hospital_robot_msgs__srv__GetPOIList_Response__Sequence
{
  hospital_robot_msgs__srv__GetPOIList_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hospital_robot_msgs__srv__GetPOIList_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__STRUCT_H_
