// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// gtest
#include <gtest/gtest.h>

// ros
#include <rclcpp/node.hpp>

// std
#include <memory>
#include <string>

// romea
#include "../test/test_helper.h"
#include "romea_mobile_base_utils/params/mobile_base_control_parameters.hpp"

class TestMobileBaseControlParams : public ::testing::Test
{
protected:
  static void SetUpTestCase()
  {
    rclcpp::init(0, nullptr);
  }

  static void TearDownTestCase()
  {
    rclcpp::shutdown();
  }

  void SetUp() override
  {
    rclcpp::NodeOptions no;
    no.arguments(
      {"--ros-args", "--params-file",
        std::string(TEST_DIR) + std::string("/test_mobile_base_control_parameters.yaml")});
    node = std::make_shared<rclcpp::Node>("test_mobile_base_control_paramerters", no);
  }

  std::shared_ptr<rclcpp::Node> node;
};


TEST_F(TestMobileBaseControlParams, getSteeringControl)
{
  romea::declare_steering_angle_control_info(node, "steering_control");
  auto control = romea::get_steering_angle_control_info(node, "steering_control");
  EXPECT_DOUBLE_EQ(control.command.maximalAngle, 1);
  EXPECT_DOUBLE_EQ(control.command.maximalAngularSpeed, 2);
  EXPECT_DOUBLE_EQ(control.sensor.angleStd, 3);
  EXPECT_DOUBLE_EQ(control.sensor.angleRange, 4);
}

TEST_F(TestMobileBaseControlParams, getSpeedControl)
{
  romea::declare_wheel_speed_control_info(node, "speed_control");
  auto control = romea::get_wheel_speed_control_info(node, "speed_control");
  EXPECT_DOUBLE_EQ(control.command.maximalSpeed, 5);
  EXPECT_DOUBLE_EQ(control.command.maximalAcceleration, 6);
  EXPECT_DOUBLE_EQ(control.sensor.speedStd, 7);
  EXPECT_DOUBLE_EQ(control.sensor.speedRange, 8);
}


//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
