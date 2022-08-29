#include "romea_mobile_base_controllers/interfaces/controller_interface1FAS2FWD.hpp"
#include <romea_common_utils/params/node_parameters.hpp>

namespace {
const std::string front_axle_steering_joint_param_name="front_axle_steering_joint_name";
const std::string front_left_wheel_spinning_joint_param_name="front_left_wheel_spinning_joint_name";
const std::string front_right_wheel_spinning_joint_param_name="front_right_wheel_spinning_joint_name";
}

namespace romea
{

//-----------------------------------------------------------------------------
ControllerInterface1FAS2FWD::ControllerInterface1FAS2FWD(
    const MobileBaseInfo1FAS2FWD & mobile_base_info):
  front_wheel_radius_(mobile_base_info.geometry.frontAxle.wheels.radius)
{
}

//-----------------------------------------------------------------------------
void ControllerInterface1FAS2FWD::write(const OdometryFrame1FAS2FWD & command,
                                        LoanedCommandInterfaces & loaned_command_interfaces)const
{
  loaned_command_interfaces[FRONT_AXLE_STEERING_JOINT_ID].
      set_value(command.frontAxleSteeringAngle);
  loaned_command_interfaces[FRONT_LEFT_WHEEL_SPINNING_JOINT_ID]
      .set_value(command.frontLeftWheelLinearSpeed/front_wheel_radius_);
  loaned_command_interfaces[FRONT_RIGHT_WHEEL_SPINNING_JOINT_ID].
      set_value(command.frontRightWheelLinearSpeed/front_wheel_radius_);
}

//-----------------------------------------------------------------------------
void ControllerInterface1FAS2FWD::read(const LoanedStateInterfaces & loaned_state_interfaces,
                                       OdometryFrame1FAS2FWD &measurement)const
{
  measurement.frontAxleSteeringAngle =
      loaned_state_interfaces[FRONT_AXLE_STEERING_JOINT_ID].get_value();
  measurement.frontLeftWheelLinearSpeed = front_wheel_radius_*
      loaned_state_interfaces[FRONT_LEFT_WHEEL_SPINNING_JOINT_ID].get_value();
  measurement.frontRightWheelLinearSpeed = front_wheel_radius_*
      loaned_state_interfaces[FRONT_RIGHT_WHEEL_SPINNING_JOINT_ID].get_value();
}


//-----------------------------------------------------------------------------
void ControllerInterface1FAS2FWD::declare_joints_names(
    std::shared_ptr<rclcpp::Node> node, const std::string & parameters_ns)
{
  declare_parameter<std::string>(node,parameters_ns,front_axle_steering_joint_param_name);
  declare_parameter<std::string>(node,parameters_ns,front_left_wheel_spinning_joint_param_name);
  declare_parameter<std::string>(node,parameters_ns,front_right_wheel_spinning_joint_param_name);
}

//-----------------------------------------------------------------------------
std::vector<std::string> ControllerInterface1FAS2FWD::get_joints_names(
    std::shared_ptr<rclcpp::Node> node, const std::string & parameters_ns)
{
  return {get_parameter<std::string>(node,parameters_ns,front_axle_steering_joint_param_name),
        get_parameter<std::string>(node,parameters_ns,front_left_wheel_spinning_joint_param_name),
        get_parameter<std::string>(node,parameters_ns,front_right_wheel_spinning_joint_param_name)};
}

//-----------------------------------------------------------------------------
std::vector<std::string> ControllerInterface1FAS2FWD::hardware_interface_names(
    const std::vector<std::string> & joints_names)
{
  return {hardware_position_interface_name(joints_names[FRONT_AXLE_STEERING_JOINT_ID]),
        hardware_velocity_interface_name(joints_names[FRONT_LEFT_WHEEL_SPINNING_JOINT_ID]),
        hardware_velocity_interface_name(joints_names[FRONT_RIGHT_WHEEL_SPINNING_JOINT_ID])};
}


}

