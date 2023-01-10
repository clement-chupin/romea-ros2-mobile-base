// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_MOBILE_BASE_HARDWARE__HARDWARE_INFO_HPP_
#define ROMEA_MOBILE_BASE_HARDWARE__HARDWARE_INFO_HPP_

// romea
#include <romea_core_common/lexical/LexicalCast.hpp>

// ros
#include <hardware_interface/hardware_info.hpp>

// std
#include <string>

namespace romea
{


const hardware_interface::ComponentInfo &
get_joint_info(
  const hardware_interface::HardwareInfo & hardware_info,
  const std::string & joint_name);

const hardware_interface::InterfaceInfo &
get_command_interface_info(
  const hardware_interface::ComponentInfo & component_info,
  const std::string & interface_name);

const hardware_interface::InterfaceInfo &
get_state_interface_info(
  const hardware_interface::ComponentInfo & component_info,
  const std::string & interface_name);

double get_min(const hardware_interface::InterfaceInfo & interface_info);

double get_max(const hardware_interface::InterfaceInfo & interface_info);


bool has_parameter(
  const hardware_interface::HardwareInfo & hardware_info,
  const std::string & parameter_name);

const std::string & get_parameter(
  const hardware_interface::HardwareInfo & hardware_info,
  const std::string & parameter_name);

template<typename T>
T get_parameter(
  const hardware_interface::HardwareInfo & hardware_info,
  const std::string & parameter_name)
{
  std::string parameter = get_parameter(hardware_info, parameter_name);

  if constexpr (std::is_same_v<T, std::string>)
  {
    return parameter;
  } else {
    return lexical_cast<T>(parameter);
  }
}

template<typename T>
T get_parameter_or(
  const hardware_interface::HardwareInfo & hardware_info,
  const std::string & parameter_name,
  const T & default_value)
{
  if (has_parameter(hardware_info, parameter_name)) {
    return get_parameter<T>(hardware_info, parameter_name);
  } else {
    return default_value;
  }
}

}  // namespace romea

#endif  // ROMEA_MOBILE_BASE_HARDWARE__HARDWARE_INFO_HPP_
