//
// Created by shivesh on 9/13/19.
//

#ifndef ARS_40X_ARS_40X_RVIZ_HPP
#define ARS_40X_ARS_40X_RVIZ_HPP

// #include <ros/ros.h>
#include <rclcpp/rclcpp.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#include "perception_ros2_msgs/msg/object_list.hpp"
#include "perception_ros2_msgs/msg/cluster_list.hpp"
namespace ars_40X {
enum {
  POINT,
  CAR,
  TRUCK,
  PEDESTRIAN,
  MOTORCYCLE,
  BICYCLE,
  WIDE,
  RESERVED
};

enum {
  INVALID,
  PERCENT_25,
  PERCENT_50,
  PERCENT_75,
  PERCENT_90,
  PERCENT_99,
  PERCENT_99_9,
  PERCENT_100
};

class ContinentalRadarRViz  : public rclcpp::Node{
 public:
  ContinentalRadarRViz();

  ~ContinentalRadarRViz();

 private:
  void clusters_callback(perception_ros2_msgs::msg::ClusterList::SharedPtr cluster_list);

  void objects_callback(perception_ros2_msgs::msg::ObjectList::SharedPtr object_list);

  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr clusters_pub_;

  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr objects_pub_;

  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr velocity_pub_;

  rclcpp::Subscription<perception_ros2_msgs::msg::ClusterList>::SharedPtr clusters_sub_;

  rclcpp::Subscription<perception_ros2_msgs::msg::ObjectList>::SharedPtr objects_sub_;
};
}

#endif //ARS_40X_ARS_40X_RVIZ_HPP
