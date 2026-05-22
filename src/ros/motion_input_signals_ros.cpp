//
// Created by shivesh on 9/14/19.
//

#include "ars_40X/ros/motion_input_signals_ros.hpp"

namespace ars_40X {
MotionInputSignalsROS::MotionInputSignalsROS(rclcpp::Node& nh, ARS_40X_CAN *ars_40X_can, std::string port_id) :
node_(nh), ars_40X_can_(ars_40X_can) {
  speed_information_ = ars_40X_can_->get_speed_information();
  yaw_rate_information_ = ars_40X_can_->get_yaw_rate_information();
  odom_sub_ = node_.create_subscription<nav_msgs::msg::Odometry>("odom" + port_id, 10, std::bind(&MotionInputSignalsROS::odom_callback, this, std::placeholders::_1));
}

MotionInputSignalsROS::~MotionInputSignalsROS() {
}

void MotionInputSignalsROS::odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
  double speed = msg->twist.twist.linear.x;
  speed_information_->set_speed(std::abs(speed));
  if (speed < 0.0) {
    speed_information_->set_speed_direction(motion_input_signals::BACKWARD);
  } else if (speed > 0.0) {
    speed_information_->set_speed_direction(motion_input_signals::FORWARD);
  } else {
    speed_information_->set_speed_direction(motion_input_signals::STANDSTILL);
  }
  ars_40X_can_->send_radar_data(can_messages::SpeedInformation);

  yaw_rate_information_->set_yaw_rate(msg->twist.twist.angular.z * 180.0 / M_PI);
  ars_40X_can_->send_radar_data(can_messages::YawRateInformation);
}
}
