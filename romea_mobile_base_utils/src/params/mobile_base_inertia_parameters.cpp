// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// romea
#include <romea_common_utils/params/eigen_parameters.hpp>

// std
#include <memory>
#include <string>

// local
#include "romea_mobile_base_utils/params/mobile_base_inertia_parameters.hpp"

namespace
{
const char mass_param_name[] = "mass";
const char center_param_name[] = "center";
const char z_moment_param_name[] = "z_moment";

}

namespace romea
{

//-----------------------------------------------------------------------------
void declare_inertia_info(
  std::shared_ptr<rclcpp::Node> node,
  const std::string & parameters_ns)
{
  declare_parameter<double>(node, parameters_ns, mass_param_name);

  declare_eigen_vector_parameter_with_default<Eigen::Vector3d>(
    node, parameters_ns, center_param_name, Eigen::Vector3d::Zero());

  declare_parameter<double>(node, parameters_ns, z_moment_param_name);
}

////-----------------------------------------------------------------------------
// void get_inertia_info(std::shared_ptr<rclcpp::Node> node,
//                      const std::string & parameters_ns,
//                      MobileBaseInertia & inertia_info)
//{
//  inertia_info.mass = get_parameter<double>(node,parameters_ns,mass_param_name);

//  inertia_info.center = get_eigen_vector_parameter<Eigen::Vector3d>(
//        node,parameters_ns,center_param_name);

//  inertia_info.zMoment = get_parameter<double>(node,parameters_ns,z_moment_param_name);
//}

//-----------------------------------------------------------------------------
MobileBaseInertia get_inertia_info(
  std::shared_ptr<rclcpp::Node> node,
  const std::string & parameters_ns)
{
  return{get_parameter<double>(node, parameters_ns, mass_param_name),
    get_eigen_vector_parameter<Eigen::Vector3d>(node, parameters_ns, center_param_name),
    get_parameter<double>(node, parameters_ns, z_moment_param_name)};
}


}  // namespace romea
