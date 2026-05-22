//
// Created by shivesh on 9/14/19.
//

#ifndef ARS_40X_OBJECT_LIST_ROS_HPP
#define ARS_40X_OBJECT_LIST_ROS_HPP

// #include <ros/ros.h>
#include <rclcpp/rclcpp.hpp>
#include <cstdint>
#include <cstddef>

// #include "ars_40X/ObjectList.h"
#include "perception_ros2_msgs/msg/object_list.hpp"
#include "ars_40X/ars_40X_can.hpp"

namespace ars_40X {
class ObjectListROS {
 public:
  ObjectListROS(rclcpp::Node& nh, ARS_40X_CAN *continentalRadarCAN, std::string port_id);

  ~ObjectListROS();

  void set_frame_id(std::string frame_id);

  void send_object_0_status();

  void send_object_1_general();

  void send_object_2_quality();

  void send_object_3_extended();

 private:
  rclcpp::Node& node_;
  std::string frame_id_;

  rclcpp::Publisher<perception_ros2_msgs::msg::ObjectList>::SharedPtr objects_data_pub_;

  ARS_40X_CAN *ars_40X_can_;

  perception_ros2_msgs::msg::ObjectList object_list;

  object_list::Object_0_Status *object_0_status_;

  object_list::Object_1_General *object_1_general_;

  object_list::Object_2_Quality *object_2_quality_;

  object_list::Object_3_Extended *object_3_extended_;

  std::size_t object_2_quality_id_ = 0;

  std::size_t object_3_extended_id_ = 0;
};
}

#endif //ARS_40X_OBJECT_LIST_ROS_HPP
