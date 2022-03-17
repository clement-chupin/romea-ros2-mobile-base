#ifndef _romea_ControllerInterface1FAS2FWD_hpp_
#define _romea_ControllerInterface1FAS2FWD_hpp_

//romea
#include "steering_joint_controller_interface.hpp"
#include "spinning_joint_controller_interface.hpp"
#include <romea_core_mobile_base/odometry/OdometryFrame1FAS2FWD.hpp>
#include <romea_core_mobile_base/info/MobileBaseInfo1FAS2FWD.hpp>

namespace romea
{

class ControllerInterface1FAS2FWD
{

public:

  using LoanedCommandInterfaces = JointControllerInterface::LoanedCommandInterfaces;
  using LoanedStateInterfaces = JointControllerInterface::LoanedStateInterfaces;

  enum JointIds
  {
    FRONT_AXLE_STEERING_JOINT_ID,
    FRONT_LEFT_WHEEL_SPINNING_JOINT_ID,
    FRONT_RIGHT_WHEEL_SPINNING_JOINT_ID
  };

public:

  ControllerInterface1FAS2FWD(const MobileBaseInfo1FAS2FWD & mobile_base_info,
                              const std::map<int,std::string> & joint_mappings,
                              LoanedCommandInterfaces & loaned_command_interfaces,
                              LoanedStateInterfaces & loaned_state_interfaces);

  OdometryFrame1FAS2FWD getOdometryFrame() const;

  void setCommand(const OdometryFrame1FAS2FWD & cmd);

  std::vector<std::string> getCommandInterfaceNames()const;

  std::vector<std::string> getStateInterfaceNames()const;

public:

  static void declare_joints_mapping(std::shared_ptr<rclcpp::Node> node,
                                     const std::string & parameters_ns);

  static std::map<int,std::string> get_joints_mapping(std::shared_ptr<rclcpp::Node> node,
                                                      const std::string & parameters_ns);

private :

  SteeringJointControllerInterface front_steering_joint_;
  SpinningJointControllerInterface front_left_spinning_joint_;
  SpinningJointControllerInterface front_right_spinning_joint_;

};


}

#endif
