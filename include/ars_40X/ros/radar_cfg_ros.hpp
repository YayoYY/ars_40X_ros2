//
// Created by shivesh on 9/14/19.
//

#ifndef ARS_40X_RADAR_CFG_ROS_HPP
#define ARS_40X_RADAR_CFG_ROS_HPP

#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/set_bool.hpp>

#include <cstdint>
#include <memory>
#include <string>

#include "ars_40X/ars_40X_can.hpp"
#include "perception_ros2_msgs/srv/max_distance.hpp"
#include "perception_ros2_msgs/srv/output_type.hpp"
#include "perception_ros2_msgs/srv/radar_power.hpp"
#include "perception_ros2_msgs/srv/rcs_threshold.hpp"
#include "perception_ros2_msgs/srv/sensor_id.hpp"
#include "perception_ros2_msgs/srv/sort_index.hpp"

namespace ars_40X {
class RadarCfgROS{
 public:
  RadarCfgROS(rclcpp::Node& nh, ARS_40X_CAN *ars_40X_can, std::string port_id);
  ~RadarCfgROS();

  bool set_max_distance(
      const std::shared_ptr<perception_ros2_msgs::srv::MaxDistance::Request> request,
      std::shared_ptr<perception_ros2_msgs::srv::MaxDistance::Response> response);

  bool set_sensor_id(
      const std::shared_ptr<perception_ros2_msgs::srv::SensorID::Request> request,
      std::shared_ptr<perception_ros2_msgs::srv::SensorID::Response> response);

  bool set_radar_power(
      const std::shared_ptr<perception_ros2_msgs::srv::RadarPower::Request> request,
      std::shared_ptr<perception_ros2_msgs::srv::RadarPower::Response> response);

  bool set_output_type(
      const std::shared_ptr<perception_ros2_msgs::srv::OutputType::Request> request,
      std::shared_ptr<perception_ros2_msgs::srv::OutputType::Response> response);

  bool set_send_quality(
      const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
      std::shared_ptr<std_srvs::srv::SetBool::Response> response);

  bool set_send_ext_info(
      const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
      std::shared_ptr<std_srvs::srv::SetBool::Response> response);

  bool set_sort_index(
      const std::shared_ptr<perception_ros2_msgs::srv::SortIndex::Request> request,
      std::shared_ptr<perception_ros2_msgs::srv::SortIndex::Response> response);

  bool set_ctrl_relay_cfg(
      const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
      std::shared_ptr<std_srvs::srv::SetBool::Response> response);

  bool set_store_in_nvm(
      const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
      std::shared_ptr<std_srvs::srv::SetBool::Response> response);

  bool set_rcs_threshold(
      const std::shared_ptr<perception_ros2_msgs::srv::RCSThreshold::Request> request,
      std::shared_ptr<perception_ros2_msgs::srv::RCSThreshold::Response> response);

  rclcpp::Node& node_;
  ARS_40X_CAN *ars_40X_can_;
  
  radar_cfg::RadarCfg *radar_cfg_;

  rclcpp::Service<perception_ros2_msgs::srv::MaxDistance>::SharedPtr set_max_distance_service_;

  rclcpp::Service<perception_ros2_msgs::srv::SensorID>::SharedPtr set_sensor_id_service_;

  rclcpp::Service<perception_ros2_msgs::srv::RadarPower>::SharedPtr set_radar_power_service_;

  rclcpp::Service<perception_ros2_msgs::srv::OutputType>::SharedPtr set_output_type_service_;

  rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr set_send_quality_service_;

  rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr set_send_ext_info_service_;

  rclcpp::Service<perception_ros2_msgs::srv::SortIndex>::SharedPtr set_sort_index_service_;
  
  rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr set_ctrl_relay_cfg_service_;
  
  rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr set_store_in_nvm_service_;
  
  rclcpp::Service<perception_ros2_msgs::srv::RCSThreshold>::SharedPtr set_rcs_threshold_service_;
};
}

#endif //ARS_40X_RADAR_CFG_ROS_HPP