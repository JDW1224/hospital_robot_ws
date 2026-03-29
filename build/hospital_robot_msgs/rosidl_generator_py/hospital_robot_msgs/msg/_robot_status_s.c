// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from hospital_robot_msgs:msg/RobotStatus.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "hospital_robot_msgs/msg/detail/robot_status__struct.h"
#include "hospital_robot_msgs/msg/detail/robot_status__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool hospital_robot_msgs__msg__robot_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[50];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("hospital_robot_msgs.msg._robot_status.RobotStatus", full_classname_dest, 49) == 0);
  }
  hospital_robot_msgs__msg__RobotStatus * ros_message = _ros_message;
  {  // nav_state
    PyObject * field = PyObject_GetAttrString(_pymsg, "nav_state");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->nav_state, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // estop_state
    PyObject * field = PyObject_GetAttrString(_pymsg, "estop_state");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->estop_state, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // current_goal_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "current_goal_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->current_goal_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // current_x
    PyObject * field = PyObject_GetAttrString(_pymsg, "current_x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->current_x = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // current_y
    PyObject * field = PyObject_GetAttrString(_pymsg, "current_y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->current_y = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // current_yaw
    PyObject * field = PyObject_GetAttrString(_pymsg, "current_yaw");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->current_yaw = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // battery_percent
    PyObject * field = PyObject_GetAttrString(_pymsg, "battery_percent");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->battery_percent = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * hospital_robot_msgs__msg__robot_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of RobotStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("hospital_robot_msgs.msg._robot_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "RobotStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  hospital_robot_msgs__msg__RobotStatus * ros_message = (hospital_robot_msgs__msg__RobotStatus *)raw_ros_message;
  {  // nav_state
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->nav_state.data,
      strlen(ros_message->nav_state.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "nav_state", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // estop_state
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->estop_state.data,
      strlen(ros_message->estop_state.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "estop_state", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // current_goal_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->current_goal_id.data,
      strlen(ros_message->current_goal_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "current_goal_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // current_x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->current_x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "current_x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // current_y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->current_y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "current_y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // current_yaw
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->current_yaw);
    {
      int rc = PyObject_SetAttrString(_pymessage, "current_yaw", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // battery_percent
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->battery_percent);
    {
      int rc = PyObject_SetAttrString(_pymessage, "battery_percent", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
