// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hospital_robot_msgs:srv/GetPOIList.idl
// generated code does not contain a copyright notice

#ifndef HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__STRUCT_HPP_
#define HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hospital_robot_msgs__srv__GetPOIList_Request __attribute__((deprecated))
#else
# define DEPRECATED__hospital_robot_msgs__srv__GetPOIList_Request __declspec(deprecated)
#endif

namespace hospital_robot_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetPOIList_Request_
{
  using Type = GetPOIList_Request_<ContainerAllocator>;

  explicit GetPOIList_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit GetPOIList_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations

  // pointer types
  using RawPtr =
    hospital_robot_msgs::srv::GetPOIList_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const hospital_robot_msgs::srv::GetPOIList_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hospital_robot_msgs::srv::GetPOIList_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hospital_robot_msgs::srv::GetPOIList_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hospital_robot_msgs::srv::GetPOIList_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hospital_robot_msgs::srv::GetPOIList_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hospital_robot_msgs::srv::GetPOIList_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hospital_robot_msgs::srv::GetPOIList_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hospital_robot_msgs::srv::GetPOIList_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hospital_robot_msgs::srv::GetPOIList_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hospital_robot_msgs__srv__GetPOIList_Request
    std::shared_ptr<hospital_robot_msgs::srv::GetPOIList_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hospital_robot_msgs__srv__GetPOIList_Request
    std::shared_ptr<hospital_robot_msgs::srv::GetPOIList_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetPOIList_Request_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetPOIList_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetPOIList_Request_

// alias to use template instance with default allocator
using GetPOIList_Request =
  hospital_robot_msgs::srv::GetPOIList_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace hospital_robot_msgs


#ifndef _WIN32
# define DEPRECATED__hospital_robot_msgs__srv__GetPOIList_Response __attribute__((deprecated))
#else
# define DEPRECATED__hospital_robot_msgs__srv__GetPOIList_Response __declspec(deprecated)
#endif

namespace hospital_robot_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetPOIList_Response_
{
  using Type = GetPOIList_Response_<ContainerAllocator>;

  explicit GetPOIList_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit GetPOIList_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _ids_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _ids_type ids;
  using _names_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _names_type names;

  // setters for named parameter idiom
  Type & set__ids(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->ids = _arg;
    return *this;
  }
  Type & set__names(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->names = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hospital_robot_msgs::srv::GetPOIList_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const hospital_robot_msgs::srv::GetPOIList_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hospital_robot_msgs::srv::GetPOIList_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hospital_robot_msgs::srv::GetPOIList_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hospital_robot_msgs::srv::GetPOIList_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hospital_robot_msgs::srv::GetPOIList_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hospital_robot_msgs::srv::GetPOIList_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hospital_robot_msgs::srv::GetPOIList_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hospital_robot_msgs::srv::GetPOIList_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hospital_robot_msgs::srv::GetPOIList_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hospital_robot_msgs__srv__GetPOIList_Response
    std::shared_ptr<hospital_robot_msgs::srv::GetPOIList_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hospital_robot_msgs__srv__GetPOIList_Response
    std::shared_ptr<hospital_robot_msgs::srv::GetPOIList_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetPOIList_Response_ & other) const
  {
    if (this->ids != other.ids) {
      return false;
    }
    if (this->names != other.names) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetPOIList_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetPOIList_Response_

// alias to use template instance with default allocator
using GetPOIList_Response =
  hospital_robot_msgs::srv::GetPOIList_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace hospital_robot_msgs

namespace hospital_robot_msgs
{

namespace srv
{

struct GetPOIList
{
  using Request = hospital_robot_msgs::srv::GetPOIList_Request;
  using Response = hospital_robot_msgs::srv::GetPOIList_Response;
};

}  // namespace srv

}  // namespace hospital_robot_msgs

#endif  // HOSPITAL_ROBOT_MSGS__SRV__DETAIL__GET_POI_LIST__STRUCT_HPP_
