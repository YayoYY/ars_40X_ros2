//
// Created by shivesh on 9/14/19.
//

#ifndef ARS_40X_RADAR_STATE_ROS_HPP
#define ARS_40X_RADAR_STATE_ROS_HPP

// #include <ros/ros.h>
#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/set_bool.hpp>

#include <cstdint>

#include "ars_40X/ars_40X_can.hpp"
#include "perception_ros2_msgs/msg/radar_status.hpp"

namespace ars_40X {
class RadarStateROS {
 public:
  RadarStateROS(rclcpp::Node& nh, ARS_40X_CAN *ars_40X_can, std::string port_id);

  ~RadarStateROS();

  void send_radar_state();

 private:
  rclcpp::Node& node_;
  rclcpp::Publisher<perception_ros2_msgs::msg::RadarStatus>::SharedPtr radar_state_pub_;

  ARS_40X_CAN *ars_40X_can_;

  radar_state::RadarState *radar_state_;
};
}

#endif //ARS_40X_RADAR_STATE_ROS_HPP
