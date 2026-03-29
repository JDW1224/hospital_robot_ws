// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from hospital_robot_msgs:srv/GetPOIList.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "hospital_robot_msgs/srv/detail/get_poi_list__rosidl_typesupport_introspection_c.h"
#include "hospital_robot_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "hospital_robot_msgs/srv/detail/get_poi_list__functions.h"
#include "hospital_robot_msgs/srv/detail/get_poi_list__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void hospital_robot_msgs__srv__GetPOIList_Request__rosidl_typesupport_introspection_c__GetPOIList_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  hospital_robot_msgs__srv__GetPOIList_Request__init(message_memory);
}

void hospital_robot_msgs__srv__GetPOIList_Request__rosidl_typesupport_introspection_c__GetPOIList_Request_fini_function(void * message_memory)
{
  hospital_robot_msgs__srv__GetPOIList_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember hospital_robot_msgs__srv__GetPOIList_Request__rosidl_typesupport_introspection_c__GetPOIList_Request_message_member_array[1] = {
  {
    "structure_needs_at_least_one_member",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hospital_robot_msgs__srv__GetPOIList_Request, structure_needs_at_least_one_member),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers hospital_robot_msgs__srv__GetPOIList_Request__rosidl_typesupport_introspection_c__GetPOIList_Request_message_members = {
  "hospital_robot_msgs__srv",  // message namespace
  "GetPOIList_Request",  // message name
  1,  // number of fields
  sizeof(hospital_robot_msgs__srv__GetPOIList_Request),
  hospital_robot_msgs__srv__GetPOIList_Request__rosidl_typesupport_introspection_c__GetPOIList_Request_message_member_array,  // message members
  hospital_robot_msgs__srv__GetPOIList_Request__rosidl_typesupport_introspection_c__GetPOIList_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  hospital_robot_msgs__srv__GetPOIList_Request__rosidl_typesupport_introspection_c__GetPOIList_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t hospital_robot_msgs__srv__GetPOIList_Request__rosidl_typesupport_introspection_c__GetPOIList_Request_message_type_support_handle = {
  0,
  &hospital_robot_msgs__srv__GetPOIList_Request__rosidl_typesupport_introspection_c__GetPOIList_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hospital_robot_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hospital_robot_msgs, srv, GetPOIList_Request)() {
  if (!hospital_robot_msgs__srv__GetPOIList_Request__rosidl_typesupport_introspection_c__GetPOIList_Request_message_type_support_handle.typesupport_identifier) {
    hospital_robot_msgs__srv__GetPOIList_Request__rosidl_typesupport_introspection_c__GetPOIList_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &hospital_robot_msgs__srv__GetPOIList_Request__rosidl_typesupport_introspection_c__GetPOIList_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "hospital_robot_msgs/srv/detail/get_poi_list__rosidl_typesupport_introspection_c.h"
// already included above
// #include "hospital_robot_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "hospital_robot_msgs/srv/detail/get_poi_list__functions.h"
// already included above
// #include "hospital_robot_msgs/srv/detail/get_poi_list__struct.h"


// Include directives for member types
// Member `ids`
// Member `names`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__GetPOIList_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  hospital_robot_msgs__srv__GetPOIList_Response__init(message_memory);
}

void hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__GetPOIList_Response_fini_function(void * message_memory)
{
  hospital_robot_msgs__srv__GetPOIList_Response__fini(message_memory);
}

size_t hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__size_function__GetPOIList_Response__ids(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__get_const_function__GetPOIList_Response__ids(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__get_function__GetPOIList_Response__ids(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__fetch_function__GetPOIList_Response__ids(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__get_const_function__GetPOIList_Response__ids(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__assign_function__GetPOIList_Response__ids(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__get_function__GetPOIList_Response__ids(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__resize_function__GetPOIList_Response__ids(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__size_function__GetPOIList_Response__names(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__get_const_function__GetPOIList_Response__names(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__get_function__GetPOIList_Response__names(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__fetch_function__GetPOIList_Response__names(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__get_const_function__GetPOIList_Response__names(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__assign_function__GetPOIList_Response__names(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__get_function__GetPOIList_Response__names(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__resize_function__GetPOIList_Response__names(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__GetPOIList_Response_message_member_array[2] = {
  {
    "ids",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hospital_robot_msgs__srv__GetPOIList_Response, ids),  // bytes offset in struct
    NULL,  // default value
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__size_function__GetPOIList_Response__ids,  // size() function pointer
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__get_const_function__GetPOIList_Response__ids,  // get_const(index) function pointer
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__get_function__GetPOIList_Response__ids,  // get(index) function pointer
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__fetch_function__GetPOIList_Response__ids,  // fetch(index, &value) function pointer
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__assign_function__GetPOIList_Response__ids,  // assign(index, value) function pointer
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__resize_function__GetPOIList_Response__ids  // resize(index) function pointer
  },
  {
    "names",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hospital_robot_msgs__srv__GetPOIList_Response, names),  // bytes offset in struct
    NULL,  // default value
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__size_function__GetPOIList_Response__names,  // size() function pointer
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__get_const_function__GetPOIList_Response__names,  // get_const(index) function pointer
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__get_function__GetPOIList_Response__names,  // get(index) function pointer
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__fetch_function__GetPOIList_Response__names,  // fetch(index, &value) function pointer
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__assign_function__GetPOIList_Response__names,  // assign(index, value) function pointer
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__resize_function__GetPOIList_Response__names  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__GetPOIList_Response_message_members = {
  "hospital_robot_msgs__srv",  // message namespace
  "GetPOIList_Response",  // message name
  2,  // number of fields
  sizeof(hospital_robot_msgs__srv__GetPOIList_Response),
  hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__GetPOIList_Response_message_member_array,  // message members
  hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__GetPOIList_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__GetPOIList_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__GetPOIList_Response_message_type_support_handle = {
  0,
  &hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__GetPOIList_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hospital_robot_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hospital_robot_msgs, srv, GetPOIList_Response)() {
  if (!hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__GetPOIList_Response_message_type_support_handle.typesupport_identifier) {
    hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__GetPOIList_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &hospital_robot_msgs__srv__GetPOIList_Response__rosidl_typesupport_introspection_c__GetPOIList_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "hospital_robot_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "hospital_robot_msgs/srv/detail/get_poi_list__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers hospital_robot_msgs__srv__detail__get_poi_list__rosidl_typesupport_introspection_c__GetPOIList_service_members = {
  "hospital_robot_msgs__srv",  // service namespace
  "GetPOIList",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // hospital_robot_msgs__srv__detail__get_poi_list__rosidl_typesupport_introspection_c__GetPOIList_Request_message_type_support_handle,
  NULL  // response message
  // hospital_robot_msgs__srv__detail__get_poi_list__rosidl_typesupport_introspection_c__GetPOIList_Response_message_type_support_handle
};

static rosidl_service_type_support_t hospital_robot_msgs__srv__detail__get_poi_list__rosidl_typesupport_introspection_c__GetPOIList_service_type_support_handle = {
  0,
  &hospital_robot_msgs__srv__detail__get_poi_list__rosidl_typesupport_introspection_c__GetPOIList_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hospital_robot_msgs, srv, GetPOIList_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hospital_robot_msgs, srv, GetPOIList_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hospital_robot_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hospital_robot_msgs, srv, GetPOIList)() {
  if (!hospital_robot_msgs__srv__detail__get_poi_list__rosidl_typesupport_introspection_c__GetPOIList_service_type_support_handle.typesupport_identifier) {
    hospital_robot_msgs__srv__detail__get_poi_list__rosidl_typesupport_introspection_c__GetPOIList_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)hospital_robot_msgs__srv__detail__get_poi_list__rosidl_typesupport_introspection_c__GetPOIList_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hospital_robot_msgs, srv, GetPOIList_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hospital_robot_msgs, srv, GetPOIList_Response)()->data;
  }

  return &hospital_robot_msgs__srv__detail__get_poi_list__rosidl_typesupport_introspection_c__GetPOIList_service_type_support_handle;
}
