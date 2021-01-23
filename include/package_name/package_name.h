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

#include <std_msgs/Float32.h>

namespace package_name {

struct PackageNameParam {
  float param_hoge;
};

struct PackageNameInput {
  std_msgs::Float32::ConstPtr input_hoge;
};

struct PackageNameOutput {
  float output_hoge;
};

class PackageName {
public:
  void setParam(const PackageNameParam &param);
  PackageNameOutput update(const PackageNameInput &input);

private:
  PackageNameParam param_;
};

} // namespace package_name
