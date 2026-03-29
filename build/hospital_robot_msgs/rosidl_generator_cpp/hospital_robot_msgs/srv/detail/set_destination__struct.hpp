// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hospital_robot_msgs:srv/SetDestination.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__SRV__DETAIL__SET_DESTINATION__STRUCT_HPP_
#define HOSPITAL_ROBOT_MSGS__SRV__DETAIL__SET_DESTINATION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hospital_robot_msgs__srv__SetDestination_Request __attribute__((deprecated))
#else
# define DEPRECATED__hospital_robot_msgs__srv__SetDestination_Request __declspec(deprecated)
#endif

namespace hospital_robot_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetDestination_Request_
{
  using Type = SetDestination_Request_<ContainerAllocator>;

  explicit SetDestination_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->destination_id = "";
    }
  }

  explicit SetDestination_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : destination_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->destination_id = "";
    }
  }

  // field types and members
  using _destination_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _destination_id_type destination_id;

  // setters for named parameter idiom
  Type & set__destination_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->destination_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hospital_robot_msgs::srv::SetDestination_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const hospital_robot_msgs::srv::SetDestination_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hospital_robot_msgs::srv::SetDestination_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hospital_robot_msgs::srv::SetDestination_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hospital_robot_msgs::srv::SetDestination_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hospital_robot_msgs::srv::SetDestination_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hospital_robot_msgs::srv::SetDestination_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hospital_robot_msgs::srv::SetDestination_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hospital_robot_msgs::srv::SetDestination_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hospital_robot_msgs::srv::SetDestination_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hospital_robot_msgs__srv__SetDestination_Request
    std::shared_ptr<hospital_robot_msgs::srv::SetDestination_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hospital_robot_msgs__srv__SetDestination_Request
    std::shared_ptr<hospital_robot_msgs::srv::SetDestination_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetDestination_Request_ & other) const
  {
    if (this->destination_id != other.destination_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetDestination_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetDestination_Request_

// alias to use template instance with default allocator
using SetDestination_Request =
  hospital_robot_msgs::srv::SetDestination_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace hospital_robot_msgs


#ifndef _WIN32
# define DEPRECATED__hospital_robot_msgs__srv__SetDestination_Response __attribute__((deprecated))
#else
# define DEPRECATED__hospital_robot_msgs__srv__SetDestination_Response __declspec(deprecated)
#endif

namespace hospital_robot_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetDestination_Response_
{
  using Type = SetDestination_Response_<ContainerAllocator>;

  explicit SetDestination_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
      this->goal_x = 0.0;
      this->goal_y = 0.0;
      this->goal_yaw = 0.0;
    }
  }

  explicit SetDestination_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
      this->goal_x = 0.0;
      this->goal_y = 0.0;
      this->goal_yaw = 0.0;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _goal_x_type =
    double;
  _goal_x_type goal_x;
  using _goal_y_type =
    double;
  _goal_y_type goal_y;
  using _goal_yaw_type =
    double;
  _goal_yaw_type goal_yaw;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }
  Type & set__goal_x(
    const double & _arg)
  {
    this->goal_x = _arg;
    return *this;
  }
  Type & set__goal_y(
    const double & _arg)
  {
    this->goal_y = _arg;
    return *this;
  }
  Type & set__goal_yaw(
    const double & _arg)
  {
    this->goal_yaw = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hospital_robot_msgs::srv::SetDestination_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const hospital_robot_msgs::srv::SetDestination_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hospital_robot_msgs::srv::SetDestination_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hospital_robot_msgs::srv::SetDestination_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hospital_robot_msgs::srv::SetDestination_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hospital_robot_msgs::srv::SetDestination_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hospital_robot_msgs::srv::SetDestination_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hospital_robot_msgs::srv::SetDestination_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hospital_robot_msgs::srv::SetDestination_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hospital_robot_msgs::srv::SetDestination_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hospital_robot_msgs__srv__SetDestination_Response
    std::shared_ptr<hospital_robot_msgs::srv::SetDestination_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hospital_robot_msgs__srv__SetDestination_Response
    std::shared_ptr<hospital_robot_msgs::srv::SetDestination_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetDestination_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->goal_x != other.goal_x) {
      return false;
    }
    if (this->goal_y != other.goal_y) {
      return false;
    }
    if (this->goal_yaw != other.goal_yaw) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetDestination_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetDestination_Response_

// alias to use template instance with default allocator
using SetDestination_Response =
  hospital_robot_msgs::srv::SetDestination_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace hospital_robot_msgs

namespace hospital_robot_msgs
{

namespace srv
{

struct SetDestination
{
  using Request = hospital_robot_msgs::srv::SetDestination_Request;
  using Response = hospital_robot_msgs::srv::SetDestination_Response;
};

}  // namespace srv

}  // namespace hospital_robot_msgs

#endif  // HOSPITAL_ROBOT_MSGS__SRV__DETAIL__SET_DESTINATION__STRUCT_HPP_
