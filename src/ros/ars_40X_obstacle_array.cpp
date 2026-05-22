//
// Created by shivesh on 9/18/19.
//

#include <rclcpp/rclcpp.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include "ars_40X/ros/ars_40X_rviz.hpp"
#include "ars_40X/ros/ars_40X_obstacle_array.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include "perception_ros2_msgs/msg/objects3d.hpp"

#include <iostream>

namespace ars_40X {
  
void ObstacleArray::object_list_callback(perception_ros2_msgs::msg::ObjectList::SharedPtr object_list) {
  // costmap_converter::ObstacleArrayMsg obstacle_array_msg;
  auto marker_array = visualization_msgs::msg::MarkerArray();
  // marker_array.header.frame_id = object_list.header.frame_id;
  // marker_array.header.stamp = object_list.header.stamp;
  int id = 0;
  for (auto object : object_list->objects) {
    auto marker = visualization_msgs::msg::Marker();            
    marker.header.frame_id = object_list->header.frame_id;  //"PandarXT-16";  //"radar";  //
    marker.header.stamp = object_list->header.stamp;
    marker.ns = "radar_obstacle";
    marker.id = object.id; 
    marker.type = visualization_msgs::msg::Marker::CUBE;  
    marker.action = visualization_msgs::msg::Marker::ADD;   
    marker.pose.position.x = object.position.pose.position.x;   
    marker.pose.position.y = object.position.pose.position.y;
    marker.pose.position.z = object.position.pose.position.z;
    marker.pose.orientation.w = object.position.pose.orientation.w; 
    marker.pose.orientation.x = object.position.pose.orientation.x;
    marker.pose.orientation.y = object.position.pose.orientation.y;
    marker.pose.orientation.z = object.position.pose.orientation.z;
    // marker.scale.x = object.width;          
    // marker.scale.y = object.length;
    marker.scale.x = object.length;          
    marker.scale.y = object.width;
    marker.scale.z = 1.8;
    marker.color.r = 0.0;           
    marker.color.g = 0.0;
    marker.color.b = 1.0;
    marker.color.a = 0.4;            
    marker.lifetime = rclcpp::Duration(0, 50000000);
    marker_array.markers.push_back(marker);
    
    auto text_marker = visualization_msgs::msg::Marker();
    text_marker.header.frame_id = object_list->header.frame_id;  
    text_marker.header.stamp = object_list->header.stamp;
    text_marker.ns = "ClassId";    
    text_marker.id = object.id;                   
    text_marker.type = visualization_msgs::msg::Marker::TEXT_VIEW_FACING;  
    text_marker.action = visualization_msgs::msg::Marker::ADD;             
    text_marker.pose.position.x = object.position.pose.position.x;    
    text_marker.pose.position.y = object.position.pose.position.y;
    text_marker.pose.position.z = object.position.pose.position.z + 0.5*1.8;
    text_marker.pose.orientation.w = 1.0; 
    text_marker.scale.z = 0.5;            
    text_marker.color.r = 0.0;            
    text_marker.color.g = 1.0;
    text_marker.color.b = 0.0;
    text_marker.color.a = 1.0;       
    text_marker.text = "";  
    switch (object.class_type) {
      case POINT: {
        text_marker.text = "POINT";
        break;
      }

      case CAR: {
        text_marker.text = "CAR";
        break;
      }

      case TRUCK: {
        text_marker.text = "TRUCK";
        break;
      }

      case PEDESTRIAN: {
        text_marker.text = "PEDESTRIAN";
        break;
      }

      case MOTORCYCLE: {
        text_marker.text = "MOTORCYCLE";
        break;
      }

      case BICYCLE: {
        text_marker.text = "BICYCLE";
        break;
      }

      case WIDE: {
        text_marker.text = "WIDE";
        break;
      }

      case RESERVED: {
        text_marker.text = "";
        break;
      }
    }
    float prob_of_exist = 0.0;
    switch (object.prob_of_exist) {
      case INVALID: {
        prob_of_exist = 0.0;
        break;
      }

      case PERCENT_25: {
        prob_of_exist = 0.25;
        break;
      }

      case PERCENT_50: {
        prob_of_exist = 0.5;
        break;
      }

      case PERCENT_75: {
        prob_of_exist = 0.75;
        break;
      }

      case PERCENT_90: {
        prob_of_exist = 0.9;
        break;
      }

      case PERCENT_99: {
        prob_of_exist = 0.99;
        break;
      }

      case PERCENT_99_9: {
        prob_of_exist = 0.999;
        break;
      }

      case PERCENT_100: {
        prob_of_exist = 1.0;
        break;
      }
    }
    text_marker.text.append(",ID:");
    text_marker.text.append(std::to_string(object.id));
    text_marker.text.append(",conf:");
    text_marker.text.append(std::to_string(prob_of_exist));
    text_marker.text.append(",vel:");
    text_marker.text.append(std::to_string(hypot(object.relative_velocity.twist.linear.x,
      object.relative_velocity.twist.linear.y)));
    text_marker.lifetime = rclcpp::Duration(0, 50000000);
    marker_array.markers.push_back(text_marker);

    id++;
  }
  publisher_->publish(marker_array);
}
}

int main(int argc, char **argv) {
  // ros::init(argc, argv, "obstacle_array");
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <port_id>" << std::endl;
    return 1;
  }

  rclcpp::init(argc, argv);
  auto node = std::make_shared<ars_40X::ObstacleArray>(argc, argv);
  rclcpp::spin(node);
  rclcpp::shutdown();
}
