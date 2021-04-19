/*
 * Copyright 2021 Tier IV, Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <memory>

#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Header.h>

#include <package_name_node/package_name.h>

// option
// #include <diagnostic_updater/diagnostic_updater.h>

// #include <dynamic_reconfigure/server.h>
// #include <package_name/PackageNameConfig.h>

namespace package_name
{
struct PackageNameNodeParam
{
  double update_rate;
  double th_timeout;
};

class PackageNameNode
{
public:
  PackageNameNode();

private:
  // NodeHandle
  ros::NodeHandle nh_{""};
  ros::NodeHandle private_nh_{"~"};

  // Subscriber
  ros::Subscriber sub_data_;

  // Data Buffer
  std_msgs::Float32MultiArray::ConstPtr data_hoge;
  std_msgs::Header::ConstPtr data_header;

  // Callback
  void onData(const std_msgs::Float32MultiArray::ConstPtr & msg);
  void onHeader(const std_msgs::Header::ConstPtr & msg);

  // Publisher
  ros::Publisher pub_data_;

  // Timer
  ros::Timer timer_;
  bool isDataReady();
  bool isDataTimeout();
  void onTimer(const ros::TimerEvent & event);

  // Parameter
  PackageNameNodeParam node_param_;
  PackageNameParam core_param_;

  // Dynamic Reconfigure
  // void onConfig(const PackageNameConfig & config, const uint32_t level);
  // dynamic_reconfigure::Server<PackageNameConfig> dynamic_reconfigure_;

  // Core
  PackageNameInput input_;
  PackageNameOutput output_;
  std::unique_ptr<PackageName> package_name_;

  // Diagnostic Updater
  // diagnostic_updater::Updater diagnostic_updater_;
  // void checkError(diagnostic_updater::DiagnosticStatusWrapper & stat);
};
}  // namespace package_name
