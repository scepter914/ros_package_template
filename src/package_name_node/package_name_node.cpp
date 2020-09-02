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

#include <package_name/package_name_node.h>

PackageNameNode::PackageNameNode()
{
  // Node Parameter
  private_nh_.param("update_rate", node_param_.update_rate, 10.0);

  // Core Parameter
  PackageNameParam core_param;

  // Core
  package_name_ = std::make_unique<PackageName>(core_param);

  // Subscriber
  sub_data_ = private_nh_.subscribe("input/topic_name", 1, &PackageNameNode::onData, this);

  // Publisher
  pub_data_ = private_nh_.advertise<std_msgs::Bool>("output/topic_name", 1);

  // Timer
  timer_ =
    private_nh_.createTimer(ros::Rate(node_param_.update_rate), &PackageNameNode::onTimer, this);
}

bool PackageNameNode::isDataReady()
{
  if (!data_) {
    ROS_DEBUG_THROTTLE(1.0, "waiting for data msg...");
    return false;
  }

  return true;
}

void PackageNameNode::onTimer(const ros::TimerEvent & event)
{
  if (!isDataReady()) {
    return;
  }

  package_name_->update();
}

void PackageNameNode::onData(const std_msgs::Bool::ConstPtr & msg) { data_ = msg; }
