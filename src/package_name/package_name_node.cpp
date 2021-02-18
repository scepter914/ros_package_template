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

#include <package_name/package_name_node.h>

namespace package_name
{
PackageNameNode::PackageNameNode()
{
  // Node Parameter
  private_nh_.param("update_rate", node_param_.update_rate, 10.0);
  private_nh_.param("th_timeout", node_param_.th_timeout, 0.1);

  // Core Parameter
  private_nh_.param("param_hoge", core_param_.param_hoge, 0.1f);

  // Dynamic Reconfigure
  dynamic_reconfigure_.setCallback(boost::bind(&PackageNameNode::onConfig, this, _1, _2));

  // Core
  package_name_ = std::make_unique<PackageName>();
  package_name_->setParam(core_param_);

  // Subscriber
  sub_data_ = private_nh_.subscribe("input/topic_name", 1, &PackageNameNode::onData, this);

  // Publisher
  pub_data_ = private_nh_.advertise<std_msgs::Float32>("output/topic_name", 1);

  // Diagnostic Updater
  // diagnostic_updater_.setHardwareID("package_name");

  // Timer
  timer_ =
    private_nh_.createTimer(ros::Rate(node_param_.update_rate), &PackageNameNode::onTimer, this);
}

bool PackageNameNode::isDataReady()
{
  if (!data_hoge) {
    ROS_DEBUG_THROTTLE(1.0, "waiting for data msg...");
    return false;
  }
  return true;
}

bool PackageNameNode::isDataTimeout()
{
  const auto now = ros::Time::now();
  const auto time_diff = data_header->stamp - now;
  if (time_diff.toSec() > node_param_.th_timeout) {
    ROS_WARN_THROTTLE(1.0, "pose is timeout...");
    return true;
  }
  return false;
}

void PackageNameNode::onData(const std_msgs::Float32::ConstPtr & msg) { data_hoge = msg; }

void PackageNameNode::onHeader(const std_msgs::Header::ConstPtr & msg) { data_header = msg; }

void PackageNameNode::onTimer(const ros::TimerEvent & event)
{
  if (!isDataReady()) {
    return;
  }
  if (isDataTimeout()) {
    return;
  }
  input_.input_hoge_msg = data_hoge;
  output_ = package_name_->update(input_);
  if (output_->output_hoge_msg.data.empty()){
    ROS_INFO("Output_hoge_msg.data is empty");
  } else {
    output_->output_hoge_msg.publish(pub_data_);
  }
}

void PackageNameNode::onConfig(const PackageNameConfig & config, const uint32_t level)
{
  core_param_.param_hoge = config.param_hoge;
  if (package_name_) {
    package_name_->setParam(core_param_);
  }
}

/*
void PackageNameNode::checkError(
    diagnostic_updater::DiagnosticStatusWrapper &stat) {
  int8_t level = diagnostic_msgs::DiagnosticStatus::OK;
  std::string msg = "OK";
  if (output_.is_error) {
    level = diagnostic_msgs::DiagnosticStatus::ERROR;
    msg = "package_name is Error";
  }
  stat.summary(level, msg);
}
*/
}  // namespace package_name
