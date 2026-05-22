//
// Created by shivesh on 9/14/19.
//

#ifndef ARS_40X_MOTION_INPUT_SIGNALS_ROS_HPP
#define ARS_40X_MOTION_INPUT_SIGNALS_ROS_HPP

// #include <ros/ros.h>
#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>

#include <cstdint>

#include "ars_40X/ars_40X_can.hpp"

namespace ars_40X {
class MotionInputSignalsROS {
 public:
  MotionInputSignalsROS(rclcpp::Node& nh, ARS_40X_CAN *ars_40X_can, std::string port_id);

  ~MotionInputSignalsROS();

 private:
 rclcpp::Node& node_;
 void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg);

  ARS_40X_CAN *ars_40X_can_;

  motion_input_signals::SpeedInformation *speed_information_;

  motion_input_signals::YawRateInformation *yaw_rate_information_;

  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
};
}

#endif //ARS_40X_MOTION_INPUT_SIGNALS_ROS_HPP
