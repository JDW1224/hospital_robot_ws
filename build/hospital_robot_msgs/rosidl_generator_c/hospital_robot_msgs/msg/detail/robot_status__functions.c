// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hospital_robot_msgs:msg/RobotStatus.idl
// generated code does not contain a copyright notice
#include "hospital_robot_msgs/msg/detail/robot_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `nav_state`
// Member `estop_state`
// Member `current_goal_id`
#include "rosidl_runtime_c/string_functions.h"

bool
hospital_robot_msgs__msg__RobotStatus__init(hospital_robot_msgs__msg__RobotStatus * msg)
{
  if (!msg) {
    return false;
  }
  // nav_state
  if (!rosidl_runtime_c__String__init(&msg->nav_state)) {
    hospital_robot_msgs__msg__RobotStatus__fini(msg);
    return false;
  }
  // estop_state
  if (!rosidl_runtime_c__String__init(&msg->estop_state)) {
    hospital_robot_msgs__msg__RobotStatus__fini(msg);
    return false;
  }
  // current_goal_id
  if (!rosidl_runtime_c__String__init(&msg->current_goal_id)) {
    hospital_robot_msgs__msg__RobotStatus__fini(msg);
    return false;
  }
  // current_x
  // current_y
  // current_yaw
  // battery_percent
  return true;
}

void
hospital_robot_msgs__msg__RobotStatus__fini(hospital_robot_msgs__msg__RobotStatus * msg)
{
  if (!msg) {
    return;
  }
  // nav_state
  rosidl_runtime_c__String__fini(&msg->nav_state);
  // estop_state
  rosidl_runtime_c__String__fini(&msg->estop_state);
  // current_goal_id
  rosidl_runtime_c__String__fini(&msg->current_goal_id);
  // current_x
  // current_y
  // current_yaw
  // battery_percent
}

bool
hospital_robot_msgs__msg__RobotStatus__are_equal(const hospital_robot_msgs__msg__RobotStatus * lhs, const hospital_robot_msgs__msg__RobotStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // nav_state
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->nav_state), &(rhs->nav_state)))
  {
    return false;
  }
  // estop_state
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->estop_state), &(rhs->estop_state)))
  {
    return false;
  }
  // current_goal_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->current_goal_id), &(rhs->current_goal_id)))
  {
    return false;
  }
  // current_x
  if (lhs->current_x != rhs->current_x) {
    return false;
  }
  // current_y
  if (lhs->current_y != rhs->current_y) {
    return false;
  }
  // current_yaw
  if (lhs->current_yaw != rhs->current_yaw) {
    return false;
  }
  // battery_percent
  if (lhs->battery_percent != rhs->battery_percent) {
    return false;
  }
  return true;
}

bool
hospital_robot_msgs__msg__RobotStatus__copy(
  const hospital_robot_msgs__msg__RobotStatus * input,
  hospital_robot_msgs__msg__RobotStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // nav_state
  if (!rosidl_runtime_c__String__copy(
      &(input->nav_state), &(output->nav_state)))
  {
    return false;
  }
  // estop_state
  if (!rosidl_runtime_c__String__copy(
      &(input->estop_state), &(output->estop_state)))
  {
    return false;
  }
  // current_goal_id
  if (!rosidl_runtime_c__String__copy(
      &(input->current_goal_id), &(output->current_goal_id)))
  {
    return false;
  }
  // current_x
  output->current_x = input->current_x;
  // current_y
  output->current_y = input->current_y;
  // current_yaw
  output->current_yaw = input->current_yaw;
  // battery_percent
  output->battery_percent = input->battery_percent;
  return true;
}

hospital_robot_msgs__msg__RobotStatus *
hospital_robot_msgs__msg__RobotStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hospital_robot_msgs__msg__RobotStatus * msg = (hospital_robot_msgs__msg__RobotStatus *)allocator.allocate(sizeof(hospital_robot_msgs__msg__RobotStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hospital_robot_msgs__msg__RobotStatus));
  bool success = hospital_robot_msgs__msg__RobotStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hospital_robot_msgs__msg__RobotStatus__destroy(hospital_robot_msgs__msg__RobotStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hospital_robot_msgs__msg__RobotStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hospital_robot_msgs__msg__RobotStatus__Sequence__init(hospital_robot_msgs__msg__RobotStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hospital_robot_msgs__msg__RobotStatus * data = NULL;

  if (size) {
    data = (hospital_robot_msgs__msg__RobotStatus *)allocator.zero_allocate(size, sizeof(hospital_robot_msgs__msg__RobotStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hospital_robot_msgs__msg__RobotStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hospital_robot_msgs__msg__RobotStatus__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hospital_robot_msgs__msg__RobotStatus__Sequence__fini(hospital_robot_msgs__msg__RobotStatus__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hospital_robot_msgs__msg__RobotStatus__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hospital_robot_msgs__msg__RobotStatus__Sequence *
hospital_robot_msgs__msg__RobotStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hospital_robot_msgs__msg__RobotStatus__Sequence * array = (hospital_robot_msgs__msg__RobotStatus__Sequence *)allocator.allocate(sizeof(hospital_robot_msgs__msg__RobotStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hospital_robot_msgs__msg__RobotStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hospital_robot_msgs__msg__RobotStatus__Sequence__destroy(hospital_robot_msgs__msg__RobotStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hospital_robot_msgs__msg__RobotStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hospital_robot_msgs__msg__RobotStatus__Sequence__are_equal(const hospital_robot_msgs__msg__RobotStatus__Sequence * lhs, const hospital_robot_msgs__msg__RobotStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hospital_robot_msgs__msg__RobotStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hospital_robot_msgs__msg__RobotStatus__Sequence__copy(
  const hospital_robot_msgs__msg__RobotStatus__Sequence * input,
  hospital_robot_msgs__msg__RobotStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hospital_robot_msgs__msg__RobotStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hospital_robot_msgs__msg__RobotStatus * data =
      (hospital_robot_msgs__msg__RobotStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hospital_robot_msgs__msg__RobotStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hospital_robot_msgs__msg__RobotStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hospital_robot_msgs__msg__RobotStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
