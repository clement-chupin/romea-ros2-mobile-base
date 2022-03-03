#ifndef _romea_HardwareJointCommandInterface_hpp_
#define _romea_HardwareJointCommandInterface_hpp_

#include <hardware_interface/handle.hpp>
#include <hardware_interface/hardware_info.hpp>
#include <hardware_interface/system_interface.hpp>
#include <hardware_interface/types/hardware_interface_return_values.hpp>
#include "hardware_interface/types/hardware_interface_type_values.hpp"

namespace romea
{


class HardwareCommandInterface
{

public:

  HardwareCommandInterface(const hardware_interface::ComponentInfo & joint_info,
                           const std::string & interface_type);

  void export_interface(std::vector<hardware_interface::CommandInterface> & hardware_interfaces);

  const std::string & get_interface_type() const;

  const std::string & get_joint_name() const;

  double get() const;

private:

  double command_;
  double command_min_;
  double command_max_;
  std::string joint_name_;
  std::string interface_type_;

};


class HardwareStateInterface
{

public:

  HardwareStateInterface(const hardware_interface::ComponentInfo &joint_info,
                         const std::string & interface_type);

  void export_interface(std::vector<hardware_interface::StateInterface> & state_interfaces);

  const std::string & get_interface_type() const;

  const std::string & get_joint_name() const;

  void set(const double & state);

private:

  double state_;
  double state_min_;
  double state_max_;
  std::string joint_name_;
  std::string interface_type_;

};

}

#endif






