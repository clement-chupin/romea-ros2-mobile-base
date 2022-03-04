#ifndef _romea_HardwareInterface1FAS2RWD_hpp_
#define _romea_HardwareInterface1FAS2RWD_hpp_

//romea
#include "spinning_joint_hardware_interface.hpp"
#include "steering_joint_hardware_interface.hpp"

namespace romea
{

struct HardwareInterface1FAS2RWD
{

  HardwareInterface1FAS2RWD(const hardware_interface::HardwareInfo & hardware_info,
                            const std::string & spinning_joint_command_interface_type);

  SteeringJointHardwareInterface front_axle_steering_joint;
  SpinningJointHardwareInterface rear_left_wheel_spinning_joint;
  SpinningJointHardwareInterface rear_right_wheel_spinning_joint;

  SteeringJointHardwareInterface::Feedback front_left_wheel_steering_joint_feedback;
  SteeringJointHardwareInterface::Feedback front_right_wheel_steering_joint_feedback;
  SpinningJointHardwareInterface::Feedback front_left_wheel_spinning_joint_feedback;
  SpinningJointHardwareInterface::Feedback front_right_wheel_spinning_joint_feedback;

  std::vector<hardware_interface::StateInterface> export_state_interfaces();
  std::vector<hardware_interface::CommandInterface> export_command_interfaces();

};



}

#endif
