// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// string
#include <string>

// local
#include "romea_mobile_base_gazebo/spinning_joint_gazebo_interface.hpp"

namespace romea
{

//-----------------------------------------------------------------------------
SpinningJointGazeboInterface::SpinningJointGazeboInterface(
  gazebo::physics::ModelPtr parent_model,
  const hardware_interface::ComponentInfo & joint_info,
  const std::string & command_interface_type)
{
  if (!command_interface_type.compare(hardware_interface::HW_IF_VELOCITY)) {
    control_type = RotationalMotionControlType::VELOCITY;
  } else if (!command_interface_type.compare(hardware_interface::HW_IF_EFFORT)) {
    control_type = RotationalMotionControlType::TORQUE;
  } else {
    // throw error
  }

  // std::cout << " spinning joint_info.name ";
  // std::cout << joint_info.name << std::endl;
  sim_joint_ = parent_model->GetJoint(joint_info.name);
}

//-----------------------------------------------------------------------------
void SpinningJointGazeboInterface::set_command(const double & command)
{
  if (control_type == RotationalMotionControlType::VELOCITY) {
    sim_joint_->SetVelocity(0, command);
  } else {
    sim_joint_->SetForce(0, command);
  }
}

//-----------------------------------------------------------------------------
RotationalMotionState SpinningJointGazeboInterface::get_state() const
{
  RotationalMotionState state;
  state.position = sim_joint_->Position(0);
  state.velocity = sim_joint_->GetVelocity(0);
  state.torque = sim_joint_->GetForce(0);
  return state;
}

}  // namespace romea
