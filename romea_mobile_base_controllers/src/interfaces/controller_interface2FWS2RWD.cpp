#include "romea_mobile_base_controllers/interfaces/controller_interface2FWS2RWD.hpp"
#include <romea_common_utils/params/node_parameters.hpp>

namespace  {
const std::string front_left_wheel_steering_joint_param_name="front_left_wheel_steering_joint_name";
const std::string front_right_wheel_steering_joint_param_name="front_right_wheel_steering_joint_name";
const std::string rear_left_wheel_spinning_joint_param_name="rear_left_wheel_spinning_joint_name";
const std::string rear_right_wheel_spinning_joint_param_name="rear_right_wheel_spinning_joint_name";
}

namespace romea
{

//-----------------------------------------------------------------------------
ControllerInterface2FWS2RWD::
ControllerInterface2FWS2RWD(const MobileBaseInfo2FWS2RWD & mobile_base_info,
                            const std::map<int,std::string> & joint_mappings,
                            LoanedCommandInterfaces & loaned_command_interfaces,
                            LoanedStateInterfaces & loaned_state_interfaces):
  front_left_steering_joint_(loaned_command_interfaces,
                             loaned_state_interfaces,
                             joint_mappings.at(FRONT_LEFT_WHEEL_STEERING_JOINT_ID)),
  front_right_steering_joint_(loaned_command_interfaces,
                              loaned_state_interfaces,
                              joint_mappings.at(FRONT_LEFT_WHEEL_STEERING_JOINT_ID)),
  rear_left_spinning_joint_(loaned_command_interfaces,
                            loaned_state_interfaces,
                            joint_mappings.at(REAR_LEFT_WHEEL_SPINNING_JOINT_ID),
                            mobile_base_info.geometry.rearAxle.wheels.radius),
  rear_right_spinning_joint_(loaned_command_interfaces,
                             loaned_state_interfaces,
                             joint_mappings.at(REAR_RIGHT_WHEEL_SPINNING_JOINT_ID),
                             mobile_base_info.geometry.rearAxle.wheels.radius)
{
}

//-----------------------------------------------------------------------------
void ControllerInterface2FWS2RWD::setCommand(const OdometryFrame2FWS2RWD &command)
{
  front_left_steering_joint_.setCommand(command.frontLeftWheelAngle);
  front_right_steering_joint_.setCommand(command.frontRightWheelAngle);
  rear_left_spinning_joint_.setCommand(command.rearLeftWheelSpeed);
  rear_right_spinning_joint_.setCommand(command.rearRightWheelSpeed);
}

//-----------------------------------------------------------------------------
OdometryFrame2FWS2RWD ControllerInterface2FWS2RWD::getOdometryFrame() const
{
  OdometryFrame2FWS2RWD odometry;
  odometry.frontLeftWheelAngle = front_left_steering_joint_.getMeasurement();
  odometry.frontRightWheelAngle = front_right_steering_joint_.getMeasurement();
  odometry.rearLeftWheelSpeed = rear_left_spinning_joint_.getMeasurement();
  odometry.rearRightWheelSpeed = rear_right_spinning_joint_.getMeasurement();
  return odometry;
}

//-----------------------------------------------------------------------------
std::vector<std::string> ControllerInterface2FWS2RWD::getCommandInterfaceNames()const
{
  return {front_left_steering_joint_.getCommandInterfaceName(),
        front_right_steering_joint_.getCommandInterfaceName(),
        rear_left_spinning_joint_.getCommandInterfaceName(),
        rear_right_spinning_joint_.getCommandInterfaceName()};

}

//-----------------------------------------------------------------------------
std::vector<std::string> ControllerInterface2FWS2RWD::getStateInterfaceNames()const
{
  return {front_left_steering_joint_.getStateInterfaceName(),
        front_right_steering_joint_.getStateInterfaceName(),
        rear_left_spinning_joint_.getStateInterfaceName(),
        rear_right_spinning_joint_.getStateInterfaceName()};
}

//-----------------------------------------------------------------------------
void ControllerInterface2FWS2RWD::declare_joints_mapping(
    std::shared_ptr<rclcpp::Node> node, const std::string & parameters_ns)
{
  declare_parameter<std::string>(node,parameters_ns,front_left_wheel_steering_joint_param_name);
  declare_parameter<std::string>(node,parameters_ns,front_right_wheel_steering_joint_param_name);
  declare_parameter<std::string>(node,parameters_ns,rear_left_wheel_spinning_joint_param_name);
  declare_parameter<std::string>(node,parameters_ns,rear_right_wheel_spinning_joint_param_name);
}

//-----------------------------------------------------------------------------
std::map<int,std::string> ControllerInterface2FWS2RWD::get_joints_mapping(
    std::shared_ptr<rclcpp::Node> node, const std::string & parameters_ns)
{
  std::map<int,std::string> joint_mappings;
  joint_mappings[FRONT_LEFT_WHEEL_STEERING_JOINT_ID]=
      get_parameter<std::string>(node,parameters_ns,front_left_wheel_steering_joint_param_name);
  joint_mappings[FRONT_RIGHT_WHEEL_STEERING_JOINT_ID]=
      get_parameter<std::string>(node,parameters_ns,front_right_wheel_steering_joint_param_name);
  joint_mappings[REAR_LEFT_WHEEL_SPINNING_JOINT_ID]=
      get_parameter<std::string>(node,parameters_ns,rear_left_wheel_spinning_joint_param_name);
  joint_mappings[REAR_RIGHT_WHEEL_SPINNING_JOINT_ID]=
      get_parameter<std::string>(node,parameters_ns,rear_right_wheel_spinning_joint_param_name);
  return joint_mappings;
}


}

