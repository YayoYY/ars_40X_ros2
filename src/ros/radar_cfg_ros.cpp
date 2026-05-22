//
// Created by shivesh on 9/14/19.
//

#include "ars_40X/ros/radar_cfg_ros.hpp"

namespace ars_40X {
RadarCfgROS::RadarCfgROS(rclcpp::Node& nh, ARS_40X_CAN *ars_40X_can, std::string port_id) :
    node_(nh), ars_40X_can_(ars_40X_can) {
    
    radar_cfg_ = ars_40X_can->get_radar_cfg();
    
    set_max_distance_service_ = node_.create_service<perception_ros2_msgs::srv::MaxDistance>(
        "set_max_distance" + port_id,
        std::bind(&RadarCfgROS::set_max_distance, this, std::placeholders::_1, std::placeholders::_2));
    
    set_sensor_id_service_ = node_.create_service<perception_ros2_msgs::srv::SensorID>(
        "set_sensor_id" + port_id,
        std::bind(&RadarCfgROS::set_sensor_id, this, std::placeholders::_1, std::placeholders::_2));
    
    set_radar_power_service_ = node_.create_service<perception_ros2_msgs::srv::RadarPower>(
        "set_radar_power" + port_id,
        std::bind(&RadarCfgROS::set_radar_power, this, std::placeholders::_1, std::placeholders::_2));
    
    set_output_type_service_ = node_.create_service<perception_ros2_msgs::srv::OutputType>(
        "set_output_type" + port_id,
        std::bind(&RadarCfgROS::set_output_type, this, std::placeholders::_1, std::placeholders::_2));
    
    set_send_quality_service_ = node_.create_service<std_srvs::srv::SetBool>(
        "set_send_quality" + port_id,
        std::bind(&RadarCfgROS::set_send_quality, this, std::placeholders::_1, std::placeholders::_2));
    
    set_send_ext_info_service_ = node_.create_service<std_srvs::srv::SetBool>(
        "set_send_ext_info" + port_id,
        std::bind(&RadarCfgROS::set_send_ext_info, this, std::placeholders::_1, std::placeholders::_2));
    
    set_sort_index_service_ = node_.create_service<perception_ros2_msgs::srv::SortIndex>(
        "set_sort_index" + port_id,
        std::bind(&RadarCfgROS::set_sort_index, this, std::placeholders::_1, std::placeholders::_2));
    
    set_ctrl_relay_cfg_service_ = node_.create_service<std_srvs::srv::SetBool>(
        "set_ctrl_relay_cfg" + port_id,
        std::bind(&RadarCfgROS::set_ctrl_relay_cfg, this, std::placeholders::_1, std::placeholders::_2));
    
    set_store_in_nvm_service_ = node_.create_service<std_srvs::srv::SetBool>(
        "set_store_in_nvm" + port_id,
        std::bind(&RadarCfgROS::set_store_in_nvm, this, std::placeholders::_1, std::placeholders::_2));
    
    set_rcs_threshold_service_ = node_.create_service<perception_ros2_msgs::srv::RCSThreshold>(
        "set_rcs_threshold" + port_id,
        std::bind(&RadarCfgROS::set_rcs_threshold, this, std::placeholders::_1, std::placeholders::_2));
}

RadarCfgROS::~RadarCfgROS() {
}

bool RadarCfgROS::set_max_distance(
    const std::shared_ptr<perception_ros2_msgs::srv::MaxDistance::Request> request,
    std::shared_ptr<perception_ros2_msgs::srv::MaxDistance::Response> response) {
  if (!radar_cfg_->set_max_distance(static_cast<uint64_t>(request->max_distance))) {
    return false;
  }
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_sensor_id(
    const std::shared_ptr<perception_ros2_msgs::srv::SensorID::Request> request,
    std::shared_ptr<perception_ros2_msgs::srv::SensorID::Response> response) {
  if (!radar_cfg_->set_sensor_id(request->sensor_id)) {
    return false;
  }
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_radar_power(
    const std::shared_ptr<perception_ros2_msgs::srv::RadarPower::Request> request,
    std::shared_ptr<perception_ros2_msgs::srv::RadarPower::Response> response) {
  if (!radar_cfg_->set_radar_power(request->radar_power)) {
    return false;
  }
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_output_type(
    const std::shared_ptr<perception_ros2_msgs::srv::OutputType::Request> request,
    std::shared_ptr<perception_ros2_msgs::srv::OutputType::Response> response) {
  if (!radar_cfg_->set_output_type(request->output_type)) {
    return false;
  }
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_send_quality(
    const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
    std::shared_ptr<std_srvs::srv::SetBool::Response> response) {
  radar_cfg_->set_send_quality(static_cast<bool>(request->data));
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_send_ext_info(
    const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
    std::shared_ptr<std_srvs::srv::SetBool::Response> response) {
  radar_cfg_->set_send_ext_info(static_cast<bool>(request->data));
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_sort_index(
    const std::shared_ptr<perception_ros2_msgs::srv::SortIndex::Request> request,
    std::shared_ptr<perception_ros2_msgs::srv::SortIndex::Response> response) {
  if (!radar_cfg_->set_sort_index(request->sort_index)) {
    return false;
  }
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_ctrl_relay_cfg(
    const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
    std::shared_ptr<std_srvs::srv::SetBool::Response> response) {
  radar_cfg_->set_ctrl_relay_cfg(static_cast<bool>(request->data));
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_store_in_nvm(
    const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
    std::shared_ptr<std_srvs::srv::SetBool::Response> response) {
  radar_cfg_->set_store_in_nvm(static_cast<bool>(request->data));
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

bool RadarCfgROS::set_rcs_threshold(
    const std::shared_ptr<perception_ros2_msgs::srv::RCSThreshold::Request> request,
    std::shared_ptr<perception_ros2_msgs::srv::RCSThreshold::Response> response) {
  if (!radar_cfg_->set_rcs_threshold(request->rcs_threshold)) {
    return false;
  }
  ars_40X_can_->send_radar_data(can_messages::RadarCfg);
  return true;
}

}