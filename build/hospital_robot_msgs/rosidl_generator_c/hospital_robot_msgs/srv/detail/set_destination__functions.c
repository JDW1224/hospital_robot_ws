// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hospital_robot_msgs:srv/SetDestination.idl
// generated code does not contain a copyright notice
#include "hospital_robot_msgs/srv/detail/set_destination__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `destination_id`
#include "rosidl_runtime_c/string_functions.h"

bool
hospital_robot_msgs__srv__SetDestination_Request__init(hospital_robot_msgs__srv__SetDestination_Request * msg)
{
  if (!msg) {
    return false;
  }
  // destination_id
  if (!rosidl_runtime_c__String__init(&msg->destination_id)) {
    hospital_robot_msgs__srv__SetDestination_Request__fini(msg);
    return false;
  }
  return true;
}

void
hospital_robot_msgs__srv__SetDestination_Request__fini(hospital_robot_msgs__srv__SetDestination_Request * msg)
{
  if (!msg) {
    return;
  }
  // destination_id
  rosidl_runtime_c__String__fini(&msg->destination_id);
}

bool
hospital_robot_msgs__srv__SetDestination_Request__are_equal(const hospital_robot_msgs__srv__SetDestination_Request * lhs, const hospital_robot_msgs__srv__SetDestination_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // destination_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->destination_id), &(rhs->destination_id)))
  {
    return false;
  }
  return true;
}

bool
hospital_robot_msgs__srv__SetDestination_Request__copy(
  const hospital_robot_msgs__srv__SetDestination_Request * input,
  hospital_robot_msgs__srv__SetDestination_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // destination_id
  if (!rosidl_runtime_c__String__copy(
      &(input->destination_id), &(output->destination_id)))
  {
    return false;
  }
  return true;
}

hospital_robot_msgs__srv__SetDestination_Request *
hospital_robot_msgs__srv__SetDestination_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hospital_robot_msgs__srv__SetDestination_Request * msg = (hospital_robot_msgs__srv__SetDestination_Request *)allocator.allocate(sizeof(hospital_robot_msgs__srv__SetDestination_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hospital_robot_msgs__srv__SetDestination_Request));
  bool success = hospital_robot_msgs__srv__SetDestination_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hospital_robot_msgs__srv__SetDestination_Request__destroy(hospital_robot_msgs__srv__SetDestination_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hospital_robot_msgs__srv__SetDestination_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hospital_robot_msgs__srv__SetDestination_Request__Sequence__init(hospital_robot_msgs__srv__SetDestination_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hospital_robot_msgs__srv__SetDestination_Request * data = NULL;

  if (size) {
    data = (hospital_robot_msgs__srv__SetDestination_Request *)allocator.zero_allocate(size, sizeof(hospital_robot_msgs__srv__SetDestination_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hospital_robot_msgs__srv__SetDestination_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hospital_robot_msgs__srv__SetDestination_Request__fini(&data[i - 1]);
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
hospital_robot_msgs__srv__SetDestination_Request__Sequence__fini(hospital_robot_msgs__srv__SetDestination_Request__Sequence * array)
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
      hospital_robot_msgs__srv__SetDestination_Request__fini(&array->data[i]);
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

hospital_robot_msgs__srv__SetDestination_Request__Sequence *
hospital_robot_msgs__srv__SetDestination_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hospital_robot_msgs__srv__SetDestination_Request__Sequence * array = (hospital_robot_msgs__srv__SetDestination_Request__Sequence *)allocator.allocate(sizeof(hospital_robot_msgs__srv__SetDestination_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hospital_robot_msgs__srv__SetDestination_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hospital_robot_msgs__srv__SetDestination_Request__Sequence__destroy(hospital_robot_msgs__srv__SetDestination_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hospital_robot_msgs__srv__SetDestination_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hospital_robot_msgs__srv__SetDestination_Request__Sequence__are_equal(const hospital_robot_msgs__srv__SetDestination_Request__Sequence * lhs, const hospital_robot_msgs__srv__SetDestination_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hospital_robot_msgs__srv__SetDestination_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hospital_robot_msgs__srv__SetDestination_Request__Sequence__copy(
  const hospital_robot_msgs__srv__SetDestination_Request__Sequence * input,
  hospital_robot_msgs__srv__SetDestination_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hospital_robot_msgs__srv__SetDestination_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hospital_robot_msgs__srv__SetDestination_Request * data =
      (hospital_robot_msgs__srv__SetDestination_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hospital_robot_msgs__srv__SetDestination_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hospital_robot_msgs__srv__SetDestination_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hospital_robot_msgs__srv__SetDestination_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
hospital_robot_msgs__srv__SetDestination_Response__init(hospital_robot_msgs__srv__SetDestination_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    hospital_robot_msgs__srv__SetDestination_Response__fini(msg);
    return false;
  }
  // goal_x
  // goal_y
  // goal_yaw
  return true;
}

void
hospital_robot_msgs__srv__SetDestination_Response__fini(hospital_robot_msgs__srv__SetDestination_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
  // goal_x
  // goal_y
  // goal_yaw
}

bool
hospital_robot_msgs__srv__SetDestination_Response__are_equal(const hospital_robot_msgs__srv__SetDestination_Response * lhs, const hospital_robot_msgs__srv__SetDestination_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  // goal_x
  if (lhs->goal_x != rhs->goal_x) {
    return false;
  }
  // goal_y
  if (lhs->goal_y != rhs->goal_y) {
    return false;
  }
  // goal_yaw
  if (lhs->goal_yaw != rhs->goal_yaw) {
    return false;
  }
  return true;
}

bool
hospital_robot_msgs__srv__SetDestination_Response__copy(
  const hospital_robot_msgs__srv__SetDestination_Response * input,
  hospital_robot_msgs__srv__SetDestination_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  // goal_x
  output->goal_x = input->goal_x;
  // goal_y
  output->goal_y = input->goal_y;
  // goal_yaw
  output->goal_yaw = input->goal_yaw;
  return true;
}

hospital_robot_msgs__srv__SetDestination_Response *
hospital_robot_msgs__srv__SetDestination_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hospital_robot_msgs__srv__SetDestination_Response * msg = (hospital_robot_msgs__srv__SetDestination_Response *)allocator.allocate(sizeof(hospital_robot_msgs__srv__SetDestination_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hospital_robot_msgs__srv__SetDestination_Response));
  bool success = hospital_robot_msgs__srv__SetDestination_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hospital_robot_msgs__srv__SetDestination_Response__destroy(hospital_robot_msgs__srv__SetDestination_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hospital_robot_msgs__srv__SetDestination_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hospital_robot_msgs__srv__SetDestination_Response__Sequence__init(hospital_robot_msgs__srv__SetDestination_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hospital_robot_msgs__srv__SetDestination_Response * data = NULL;

  if (size) {
    data = (hospital_robot_msgs__srv__SetDestination_Response *)allocator.zero_allocate(size, sizeof(hospital_robot_msgs__srv__SetDestination_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hospital_robot_msgs__srv__SetDestination_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hospital_robot_msgs__srv__SetDestination_Response__fini(&data[i - 1]);
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
hospital_robot_msgs__srv__SetDestination_Response__Sequence__fini(hospital_robot_msgs__srv__SetDestination_Response__Sequence * array)
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
      hospital_robot_msgs__srv__SetDestination_Response__fini(&array->data[i]);
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

hospital_robot_msgs__srv__SetDestination_Response__Sequence *
hospital_robot_msgs__srv__SetDestination_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hospital_robot_msgs__srv__SetDestination_Response__Sequence * array = (hospital_robot_msgs__srv__SetDestination_Response__Sequence *)allocator.allocate(sizeof(hospital_robot_msgs__srv__SetDestination_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hospital_robot_msgs__srv__SetDestination_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hospital_robot_msgs__srv__SetDestination_Response__Sequence__destroy(hospital_robot_msgs__srv__SetDestination_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hospital_robot_msgs__srv__SetDestination_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hospital_robot_msgs__srv__SetDestination_Response__Sequence__are_equal(const hospital_robot_msgs__srv__SetDestination_Response__Sequence * lhs, const hospital_robot_msgs__srv__SetDestination_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hospital_robot_msgs__srv__SetDestination_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hospital_robot_msgs__srv__SetDestination_Response__Sequence__copy(
  const hospital_robot_msgs__srv__SetDestination_Response__Sequence * input,
  hospital_robot_msgs__srv__SetDestination_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hospital_robot_msgs__srv__SetDestination_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hospital_robot_msgs__srv__SetDestination_Response * data =
      (hospital_robot_msgs__srv__SetDestination_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hospital_robot_msgs__srv__SetDestination_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hospital_robot_msgs__srv__SetDestination_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hospital_robot_msgs__srv__SetDestination_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
