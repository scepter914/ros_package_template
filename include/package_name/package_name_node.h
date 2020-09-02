/*
 * Copyright 2020 Tier IV, Inc. All rights reserved.
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

#include <std_msgs/Bool.h>

#include <package_name/package_name.h>

struct PackageNameNodeParam
{
  double update_rate;
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
  std_msgs::Bool::ConstPtr data_;

  // Callback
  void onData(const std_msgs::Bool::ConstPtr & msg);

  // Publisher
  ros::Publisher pub_data_;

  // Timer
  ros::Timer timer_;

  bool isDataReady();
  void onTimer(const ros::TimerEvent & event);

  // Parameter
  PackageNameNodeParam node_param_;

  // Core
  std::unique_ptr<PackageName> package_name_;
};
