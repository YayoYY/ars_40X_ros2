//
// Created by shivesh on 9/13/19.
//

#include "ars_40X/ros/ars_40X_ros.hpp"

#include <iostream>

namespace ars_40X {
ARS_40X_ROS::ARS_40X_ROS(std::string port) :
    ARS_40X_CAN(port),
    Node("ARS_40X_ROS"),
    cluster_list_ros_(*this, this, port),
    motion_input_signals_ros_(*this, this, port),
    object_list_ros_(*this, this, port),
    radar_cfg_ros_(*this, this, port),
    radar_state_ros_(*this, this, port) {
  std::string frame_id = "ARS40X";  //"radar";
  cluster_list_ros_.set_frame_id(frame_id);
  object_list_ros_.set_frame_id(frame_id);
  receive_data_thread_ = std::thread(std::bind(&ARS_40X_ROS::receive_data, this));
  receive_data_thread_.detach();
}

ARS_40X_ROS::~ARS_40X_ROS() {
}

void ARS_40X_ROS::receive_data() {
  while (rclcpp::ok()) {
    if(!receive_radar_data())
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    };
  }
}

void ARS_40X_ROS::send_cluster_0_status() {
  cluster_list_ros_.send_cluster_0_status();
}

void ARS_40X_ROS::send_cluster_1_general() {
  cluster_list_ros_.send_cluster_1_general();
}

void ARS_40X_ROS::send_cluster_2_quality() {
  cluster_list_ros_.send_cluster_2_quality();
}

void ARS_40X_ROS::send_object_0_status() {
  object_list_ros_.send_object_0_status();
}

void ARS_40X_ROS::send_object_1_general() {
  object_list_ros_.send_object_1_general();
}

void ARS_40X_ROS::send_object_2_quality() {
  object_list_ros_.send_object_2_quality();
}

void ARS_40X_ROS::send_object_3_extended() {
  object_list_ros_.send_object_3_extended();
}

void ARS_40X_ROS::send_radar_state() {
  radar_state_ros_.send_radar_state();
}

void ARS_40X_ROS::run() {
  receive_data_thread_ = std::thread(std::bind(&ARS_40X_ROS::receive_data, this));
  receive_data_thread_.detach();
}
}

int main(int argc, char **argv) {

  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <port_id>" << std::endl;
    return 1;
  }

  std::string port = argv[1];
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ars_40X::ARS_40X_ROS>(port);
  rclcpp::spin(node);
  rclcpp::shutdown();
  // ros::init(argc, argv, "ars_40X_ros");
  // ros::NodeHandle nh;
  // ars_40X::ARS_40X_ROS ars_40X_ros_(nh);
  // ars_40X_ros_.run();
  // ros::spin();
}
