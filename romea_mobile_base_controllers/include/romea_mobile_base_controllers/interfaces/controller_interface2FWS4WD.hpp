#ifndef _romea_ControllerInterface2FWS4WD_hpp_
#define _romea_ControllerInterface2FWS4WD_hpp_

#include "steering_joint_controller_interface.hpp"
#include "spinning_joint_controller_interface.hpp"
#include <romea_core_mobile_base/odometry/OdometryFrame2FWS4WD.hpp>
#include <romea_core_mobile_base/info/MobileBaseInfo2FWS4WD.hpp>

namespace romea
{

class ControllerInterface2FWS4WD
{

public:

  using LoanedCommandInterfaces = JointControllerInterface::LoanedCommandInterfaces;
  using LoanedStateInterfaces = JointControllerInterface::LoanedStateInterfaces;

  enum JointIds {
     FRONT_LEFT_WHEEL_STEERING_JOINT_ID,
     FRONT_RIGHT_WHEEL_STEERING_JOINT_ID,
     FRONT_LEFT_WHEEL_SPINNING_JOINT_ID,
     FRONT_RIGHT_WHEEL_SPINNING_JOINT_ID,
     REAR_LEFT_WHEEL_SPINNING_JOINT_ID,
     REAR_RIGHT_WHEEL_SPINNING_JOINT_ID,
  };

public:

  ControllerInterface2FWS4WD(const MobileBaseInfo2FWS4WD & mobile_base_info,
                             const std::map<int,std::string> & joint_mappings,
                             LoanedCommandInterfaces & loaned_command_interfaces,
                             LoanedStateInterfaces & loaned_state_interfaces);

  void setCommand(const OdometryFrame2FWS4WD & cmd);

  OdometryFrame2FWS4WD getOdometryFrame() const;

  std::vector<std::string> getCommandInterfaceNames()const;

  std::vector<std::string> getStateInterfaceNames()const;

  static void declare_joints_mapping(std::shared_ptr<rclcpp::Node> node,
                                     const std::string & parameters_ns);

  static std::map<int,std::string> get_joints_mapping(std::shared_ptr<rclcpp::Node> node,
                                                      const std::string & parameters_ns);

private :

  SteeringJointControllerInterface front_left_steering_joint_;
  SteeringJointControllerInterface front_right_steering_joint_;
  SpinningJointControllerInterface front_left_spinning_joint_;
  SpinningJointControllerInterface front_right_spinning_joint_;
  SpinningJointControllerInterface rear_left_spinning_joint_;
  SpinningJointControllerInterface rear_right_spinning_joint_;

};


}

#endif
