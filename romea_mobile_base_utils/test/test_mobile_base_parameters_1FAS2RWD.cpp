//gtest
#include <gtest/gtest.h>
#include "test_helper.h"

//ros
#include <rclcpp/node.hpp>

//romea
#include "romea_mobile_base_utils/params/mobile_base_parameters1FAS2RWD.hpp"


class TestMobileBaseParams1FAS2RWD : public ::testing::Test
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
    no.arguments({"--ros-args","--params-file",std::string(TEST_DIR)+"/test_mobile_base_parameters_1FAS2RWD.yaml"});
    node = std::make_shared<rclcpp::Node>("test_mobile_base_parameters_1FAS2RWD", no);
  }

  std::shared_ptr<rclcpp::Node> node;
};


TEST_F(TestMobileBaseParams1FAS2RWD, checkGetInfo)
{
  romea::declare_mobile_base_info_1FAS2RWD(node,"base");
  auto base_info=romea::get_mobile_base_info_1FAS2RWD(node,"base");

  EXPECT_DOUBLE_EQ(base_info.geometry.axlesDistance,101);
  EXPECT_DOUBLE_EQ(base_info.geometry.frontAxle.wheelsDistance,102);
  EXPECT_DOUBLE_EQ(base_info.geometry.frontAxle.wheels.radius,103);
  EXPECT_DOUBLE_EQ(base_info.geometry.frontAxle.wheels.width,104);
  EXPECT_DOUBLE_EQ(base_info.geometry.frontAxle.wheels.hubCarrierOffset,105);
  EXPECT_DOUBLE_EQ(base_info.geometry.rearAxle.wheelsDistance,106);
  EXPECT_DOUBLE_EQ(base_info.geometry.rearAxle.wheels.radius,107);
  EXPECT_DOUBLE_EQ(base_info.geometry.rearAxle.wheels.width,108);
  EXPECT_DOUBLE_EQ(base_info.geometry.rearAxle.wheels.hubCarrierOffset,109);
  EXPECT_DOUBLE_EQ(base_info.frontAxleSteeringControl.command.maximalAngle,200);
  EXPECT_DOUBLE_EQ(base_info.frontAxleSteeringControl.command.maximalAngularSpeed,201);
  EXPECT_DOUBLE_EQ(base_info.frontAxleSteeringControl.sensor.angleStd,202);
  EXPECT_DOUBLE_EQ(base_info.frontAxleSteeringControl.sensor.angleRange,203);
  EXPECT_DOUBLE_EQ(base_info.rearWheelsSpeedControl.command.maximalSpeed,300);
  EXPECT_DOUBLE_EQ(base_info.rearWheelsSpeedControl.command.maximalAcceleration,301);
  EXPECT_DOUBLE_EQ(base_info.rearWheelsSpeedControl.sensor.speedStd,302);
  EXPECT_DOUBLE_EQ(base_info.rearWheelsSpeedControl.sensor.speedRange,303);
  EXPECT_DOUBLE_EQ(base_info.inertia.mass,400);
  EXPECT_DOUBLE_EQ(base_info.inertia.center.x(),401);
  EXPECT_DOUBLE_EQ(base_info.inertia.center.y(),402);
  EXPECT_DOUBLE_EQ(base_info.inertia.center.z(),403);
  EXPECT_DOUBLE_EQ(base_info.inertia.zMoment,404);
  EXPECT_DOUBLE_EQ(base_info.controlPoint.x(),500);
  EXPECT_DOUBLE_EQ(base_info.controlPoint.y(),501);
  EXPECT_DOUBLE_EQ(base_info.controlPoint.z(),502);
}
