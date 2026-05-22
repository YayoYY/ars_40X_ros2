//
// Created by shivesh on 9/13/19.
//

#ifndef ARS_40X_OBSTACLE_ARRAY_HPP
#define ARS_40X_OBSTACLE_ARRAY_HPP

// #include <ros/ros.h>
#include "rclcpp/rclcpp.hpp"

// #include "ars_40X/ObjectList.h"
#include "perception_ros2_msgs/msg/object_list.hpp"
// #include <costmap_converter/ObstacleArrayMsg.h>

namespace ars_40X {
  class ObstacleArray : public rclcpp::Node
  {
  public:
      ObstacleArray(int argc, char * argv[])
      : Node("ObstacleArray")
      {
        std::string port_id = argv[1];
        subscription_ = this->create_subscription<perception_ros2_msgs::msg::ObjectList>(
          "ars_40X/objects" + port_id, 10,
          std::bind(&ObstacleArray::object_list_callback, this, std::placeholders::_1));
        publisher_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("radar_obstacles" + port_id, 10);
         
      }
      ~ObstacleArray()
      {
      }  
  private:
      void object_list_callback(perception_ros2_msgs::msg::ObjectList::SharedPtr object_list);
      rclcpp::Subscription<perception_ros2_msgs::msg::ObjectList>::SharedPtr subscription_;
      rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr publisher_;
  };
// class ObstacleArray {
//  public:
//   ObstacleArray();

//   ~ObstacleArray();

//  private:
//   void object_list_callback(perception_ros2_msgs::msg::ObjectList object_list);

//   ros::Publisher obstacle_array_pub_;

//   ros::Subscriber object_list_sub_;
// };
}

#endif //ARS_40X_OBSTACLE_ARRAY_HPP
