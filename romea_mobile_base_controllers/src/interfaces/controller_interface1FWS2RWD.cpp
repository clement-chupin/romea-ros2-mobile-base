#include "romea_mobile_base_controllers/interfaces/controller_interface1FWS2RWD.hpp"
#include <romea_common_utils/params/node_parameters.hpp>

namespace  {
const std::string front_wheel_steering_joint_param_name="front_wheel_steering_joint_name";
const std::string rear_left_wheel_spinning_joint_param_name="rear_left_wheel_spinning_joint_name";
const std::string rear_right_wheel_spinning_joint_param_name="rear_right_wheel_spinning_joint_name";
}

namespace romea
{

//-----------------------------------------------------------------------------
ControllerInterface1FWS2RWD::
ControllerInterface1FWS2RWD(const MobileBaseInfo1FWS2RWD & mobile_base_info):
  front_steering_joint_(),
  rear_spinning_joints_(mobile_base_info.geometry.rearAxle.wheels.radius)
{
}

//-----------------------------------------------------------------------------
void ControllerInterface1FWS2RWD::write(const OdometryFrame1FWS2RWD & command,
                                        LoanedCommandInterfaces & loaned_command_interfaces)const
{
  front_steering_joint_.write(command.frontWheelAngle,loaned_command_interfaces[FRONT_WHEEL_STEERING_JOINT_ID]);
  rear_spinning_joints_.write(command.rearLeftWheelSpeed,loaned_command_interfaces[REAR_LEFT_WHEEL_SPINNING_JOINT_ID]);
  rear_spinning_joints_.write(command.rearRightWheelSpeed,loaned_command_interfaces[REAR_RIGHT_WHEEL_SPINNING_JOINT_ID]);
}

//-----------------------------------------------------------------------------
void ControllerInterface1FWS2RWD::read(const LoanedStateInterfaces & loaned_state_interfaces,
                                       OdometryFrame1FWS2RWD & measurement)const
{
  front_steering_joint_.read(loaned_state_interfaces[FRONT_WHEEL_STEERING_JOINT_ID],measurement.frontWheelAngle);
  rear_spinning_joints_.read(loaned_state_interfaces[REAR_LEFT_WHEEL_SPINNING_JOINT_ID],measurement.rearLeftWheelSpeed);
  rear_spinning_joints_.read(loaned_state_interfaces[REAR_RIGHT_WHEEL_SPINNING_JOINT_ID],measurement.rearRightWheelSpeed);

}

//-----------------------------------------------------------------------------
void ControllerInterface1FWS2RWD::declare_joints_names(
    std::shared_ptr<rclcpp::Node> node, const std::string & parameters_ns)
{
  declare_parameter<std::string>(node,parameters_ns,front_wheel_steering_joint_param_name);
  declare_parameter<std::string>(node,parameters_ns,rear_left_wheel_spinning_joint_param_name);
  declare_parameter<std::string>(node,parameters_ns,rear_right_wheel_spinning_joint_param_name);
}

//-----------------------------------------------------------------------------
std::vector<std::string> ControllerInterface1FWS2RWD::get_joints_names(
    std::shared_ptr<rclcpp::Node> node, const std::string & parameters_ns)
{
  return{get_parameter<std::string>(node,parameters_ns,front_wheel_steering_joint_param_name),
      get_parameter<std::string>(node,parameters_ns,rear_left_wheel_spinning_joint_param_name),
      get_parameter<std::string>(node,parameters_ns,rear_right_wheel_spinning_joint_param_name)};
}

//-----------------------------------------------------------------------------
std::vector<std::string> ControllerInterface1FWS2RWD::hardware_interface_names(
    const std::vector<std::string> & joints_names)
{
  return {SteeringJointControllerInterface::hardware_interface_name(
          joints_names[FRONT_WHEEL_STEERING_JOINT_ID]),
        SpinningJointControllerInterface::hardware_interface_name(
          joints_names[REAR_LEFT_WHEEL_SPINNING_JOINT_ID]),
        SpinningJointControllerInterface::hardware_interface_name(
          joints_names[REAR_RIGHT_WHEEL_SPINNING_JOINT_ID])};
}

}

