// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from hospital_robot_msgs:srv/GetPOIList.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__FUNCTIONS_H_
#define HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "hospital_robot_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "hospital_robot_msgs/srv/detail/get_poi_list__struct.h"

/// Initialize srv/GetPOIList message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * hospital_robot_msgs__srv__GetPOIList_Request
 * )) before or use
 * hospital_robot_msgs__srv__GetPOIList_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
bool
hospital_robot_msgs__srv__GetPOIList_Request__init(hospital_robot_msgs__srv__GetPOIList_Request * msg);

/// Finalize srv/GetPOIList message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
void
hospital_robot_msgs__srv__GetPOIList_Request__fini(hospital_robot_msgs__srv__GetPOIList_Request * msg);

/// Create srv/GetPOIList message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * hospital_robot_msgs__srv__GetPOIList_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
hospital_robot_msgs__srv__GetPOIList_Request *
hospital_robot_msgs__srv__GetPOIList_Request__create();

/// Destroy srv/GetPOIList message.
/**
 * It calls
 * hospital_robot_msgs__srv__GetPOIList_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
void
hospital_robot_msgs__srv__GetPOIList_Request__destroy(hospital_robot_msgs__srv__GetPOIList_Request * msg);

/// Check for srv/GetPOIList message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
bool
hospital_robot_msgs__srv__GetPOIList_Request__are_equal(const hospital_robot_msgs__srv__GetPOIList_Request * lhs, const hospital_robot_msgs__srv__GetPOIList_Request * rhs);

/// Copy a srv/GetPOIList message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
bool
hospital_robot_msgs__srv__GetPOIList_Request__copy(
  const hospital_robot_msgs__srv__GetPOIList_Request * input,
  hospital_robot_msgs__srv__GetPOIList_Request * output);

/// Initialize array of srv/GetPOIList messages.
/**
 * It allocates the memory for the number of elements and calls
 * hospital_robot_msgs__srv__GetPOIList_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
bool
hospital_robot_msgs__srv__GetPOIList_Request__Sequence__init(hospital_robot_msgs__srv__GetPOIList_Request__Sequence * array, size_t size);

/// Finalize array of srv/GetPOIList messages.
/**
 * It calls
 * hospital_robot_msgs__srv__GetPOIList_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
void
hospital_robot_msgs__srv__GetPOIList_Request__Sequence__fini(hospital_robot_msgs__srv__GetPOIList_Request__Sequence * array);

/// Create array of srv/GetPOIList messages.
/**
 * It allocates the memory for the array and calls
 * hospital_robot_msgs__srv__GetPOIList_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
hospital_robot_msgs__srv__GetPOIList_Request__Sequence *
hospital_robot_msgs__srv__GetPOIList_Request__Sequence__create(size_t size);

/// Destroy array of srv/GetPOIList messages.
/**
 * It calls
 * hospital_robot_msgs__srv__GetPOIList_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
void
hospital_robot_msgs__srv__GetPOIList_Request__Sequence__destroy(hospital_robot_msgs__srv__GetPOIList_Request__Sequence * array);

/// Check for srv/GetPOIList message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
bool
hospital_robot_msgs__srv__GetPOIList_Request__Sequence__are_equal(const hospital_robot_msgs__srv__GetPOIList_Request__Sequence * lhs, const hospital_robot_msgs__srv__GetPOIList_Request__Sequence * rhs);

/// Copy an array of srv/GetPOIList messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
bool
hospital_robot_msgs__srv__GetPOIList_Request__Sequence__copy(
  const hospital_robot_msgs__srv__GetPOIList_Request__Sequence * input,
  hospital_robot_msgs__srv__GetPOIList_Request__Sequence * output);

/// Initialize srv/GetPOIList message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * hospital_robot_msgs__srv__GetPOIList_Response
 * )) before or use
 * hospital_robot_msgs__srv__GetPOIList_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
bool
hospital_robot_msgs__srv__GetPOIList_Response__init(hospital_robot_msgs__srv__GetPOIList_Response * msg);

/// Finalize srv/GetPOIList message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
void
hospital_robot_msgs__srv__GetPOIList_Response__fini(hospital_robot_msgs__srv__GetPOIList_Response * msg);

/// Create srv/GetPOIList message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * hospital_robot_msgs__srv__GetPOIList_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
hospital_robot_msgs__srv__GetPOIList_Response *
hospital_robot_msgs__srv__GetPOIList_Response__create();

/// Destroy srv/GetPOIList message.
/**
 * It calls
 * hospital_robot_msgs__srv__GetPOIList_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
void
hospital_robot_msgs__srv__GetPOIList_Response__destroy(hospital_robot_msgs__srv__GetPOIList_Response * msg);

/// Check for srv/GetPOIList message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
bool
hospital_robot_msgs__srv__GetPOIList_Response__are_equal(const hospital_robot_msgs__srv__GetPOIList_Response * lhs, const hospital_robot_msgs__srv__GetPOIList_Response * rhs);

/// Copy a srv/GetPOIList message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
bool
hospital_robot_msgs__srv__GetPOIList_Response__copy(
  const hospital_robot_msgs__srv__GetPOIList_Response * input,
  hospital_robot_msgs__srv__GetPOIList_Response * output);

/// Initialize array of srv/GetPOIList messages.
/**
 * It allocates the memory for the number of elements and calls
 * hospital_robot_msgs__srv__GetPOIList_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
bool
hospital_robot_msgs__srv__GetPOIList_Response__Sequence__init(hospital_robot_msgs__srv__GetPOIList_Response__Sequence * array, size_t size);

/// Finalize array of srv/GetPOIList messages.
/**
 * It calls
 * hospital_robot_msgs__srv__GetPOIList_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
void
hospital_robot_msgs__srv__GetPOIList_Response__Sequence__fini(hospital_robot_msgs__srv__GetPOIList_Response__Sequence * array);

/// Create array of srv/GetPOIList messages.
/**
 * It allocates the memory for the array and calls
 * hospital_robot_msgs__srv__GetPOIList_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
hospital_robot_msgs__srv__GetPOIList_Response__Sequence *
hospital_robot_msgs__srv__GetPOIList_Response__Sequence__create(size_t size);

/// Destroy array of srv/GetPOIList messages.
/**
 * It calls
 * hospital_robot_msgs__srv__GetPOIList_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
void
hospital_robot_msgs__srv__GetPOIList_Response__Sequence__destroy(hospital_robot_msgs__srv__GetPOIList_Response__Sequence * array);

/// Check for srv/GetPOIList message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
bool
hospital_robot_msgs__srv__GetPOIList_Response__Sequence__are_equal(const hospital_robot_msgs__srv__GetPOIList_Response__Sequence * lhs, const hospital_robot_msgs__srv__GetPOIList_Response__Sequence * rhs);

/// Copy an array of srv/GetPOIList messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_hospital_robot_msgs
bool
hospital_robot_msgs__srv__GetPOIList_Response__Sequence__copy(
  const hospital_robot_msgs__srv__GetPOIList_Response__Sequence * input,
  hospital_robot_msgs__srv__GetPOIList_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__FUNCTIONS_H_
