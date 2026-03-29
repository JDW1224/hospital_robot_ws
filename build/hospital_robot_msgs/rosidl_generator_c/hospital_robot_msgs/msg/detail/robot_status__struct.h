// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hospital_robot_msgs:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__MSG__DETAIL__ROBOT_STATUS__STRUCT_H_
#define HOSPITAL_ROBOT_MSGS__MSG__DETAIL__ROBOT_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'nav_state'
// Member 'estop_state'
// Member 'current_goal_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/RobotStatus in the package hospital_robot_msgs.
/**
  * 로봇 전체 상태 메시지
 */
typedef struct hospital_robot_msgs__msg__RobotStatus
{
  /// IDLE / NAVIGATING / PAUSED / ESTOP
  rosidl_runtime_c__String nav_state;
  /// NORMAL / ESTOP
  rosidl_runtime_c__String estop_state;
  /// 현재 목표 destination_id (없으면 빈 문자열)
  rosidl_runtime_c__String current_goal_id;
  /// 현재 위치 x
  double current_x;
  /// 현재 위치 y
  double current_y;
  /// 현재 방향 (라디안)
  double current_yaw;
  /// 배터리 잔량 (확장용)
  double battery_percent;
} hospital_robot_msgs__msg__RobotStatus;

// Struct for a sequence of hospital_robot_msgs__msg__RobotStatus.
typedef struct hospital_robot_msgs__msg__RobotStatus__Sequence
{
  hospital_robot_msgs__msg__RobotStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hospital_robot_msgs__msg__RobotStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HOSPITAL_ROBOT_MSGS__MSG__DETAIL__ROBOT_STATUS__STRUCT_H_
