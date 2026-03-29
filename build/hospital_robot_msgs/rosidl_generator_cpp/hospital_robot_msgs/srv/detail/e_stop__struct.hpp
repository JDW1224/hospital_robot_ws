// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hospital_robot_msgs:srv/EStop.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__SRV__DETAIL__E_STOP__STRUCT_HPP_
#define HOSPITAL_ROBOT_MSGS__SRV__DETAIL__E_STOP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hospital_robot_msgs__srv__EStop_Request __attribute__((deprecated))
#else
# define DEPRECATED__hospital_robot_msgs__srv__EStop_Request __declspec(deprecated)
#endif

namespace hospital_robot_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct EStop_Request_
{
  using Type = EStop_Request_<ContainerAllocator>;

  explicit EStop_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->activate = false;
    }
  }

  explicit EStop_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->activate = false;
    }
  }

  // field types and members
  using _activate_type =
    bool;
  _activate_type activate;

  // setters for named parameter idiom
  Type & set__activate(
    const bool & _arg)
  {
    this->activate = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hospital_robot_msgs::srv::EStop_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const hospital_robot_msgs::srv::EStop_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hospital_robot_msgs::srv::EStop_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hospital_robot_msgs::srv::EStop_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hospital_robot_msgs::srv::EStop_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hospital_robot_msgs::srv::EStop_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hospital_robot_msgs::srv::EStop_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hospital_robot_msgs::srv::EStop_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hospital_robot_msgs::srv::EStop_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hospital_robot_msgs::srv::EStop_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hospital_robot_msgs__srv__EStop_Request
    std::shared_ptr<hospital_robot_msgs::srv::EStop_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hospital_robot_msgs__srv__EStop_Request
    std::shared_ptr<hospital_robot_msgs::srv::EStop_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EStop_Request_ & other) const
  {
    if (this->activate != other.activate) {
      return false;
    }
    return true;
  }
  bool operator!=(const EStop_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EStop_Request_

// alias to use template instance with default allocator
using EStop_Request =
  hospital_robot_msgs::srv::EStop_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace hospital_robot_msgs


#ifndef _WIN32
# define DEPRECATED__hospital_robot_msgs__srv__EStop_Response __attribute__((deprecated))
#else
# define DEPRECATED__hospital_robot_msgs__srv__EStop_Response __declspec(deprecated)
#endif

namespace hospital_robot_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct EStop_Response_
{
  using Type = EStop_Response_<ContainerAllocator>;

  explicit EStop_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->state = "";
    }
  }

  explicit EStop_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : state(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->state = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _state_type state;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hospital_robot_msgs::srv::EStop_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const hospital_robot_msgs::srv::EStop_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hospital_robot_msgs::srv::EStop_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hospital_robot_msgs::srv::EStop_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hospital_robot_msgs::srv::EStop_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hospital_robot_msgs::srv::EStop_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hospital_robot_msgs::srv::EStop_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hospital_robot_msgs::srv::EStop_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hospital_robot_msgs::srv::EStop_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hospital_robot_msgs::srv::EStop_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hospital_robot_msgs__srv__EStop_Response
    std::shared_ptr<hospital_robot_msgs::srv::EStop_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hospital_robot_msgs__srv__EStop_Response
    std::shared_ptr<hospital_robot_msgs::srv::EStop_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EStop_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    return true;
  }
  bool operator!=(const EStop_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EStop_Response_

// alias to use template instance with default allocator
using EStop_Response =
  hospital_robot_msgs::srv::EStop_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace hospital_robot_msgs

namespace hospital_robot_msgs
{

namespace srv
{

struct EStop
{
  using Request = hospital_robot_msgs::srv::EStop_Request;
  using Response = hospital_robot_msgs::srv::EStop_Response;
};

}  // namespace srv

}  // namespace hospital_robot_msgs

#endif  // HOSPITAL_ROBOT_MSGS__SRV__DETAIL__E_STOP__STRUCT_HPP_
