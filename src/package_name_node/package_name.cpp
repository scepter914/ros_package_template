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

#include <package_name_node/package_name.h>

namespace package_name
{
void PackageName::setParam(const PackageNameParam & param) { param_ = param; }

PackageNameOutput PackageName::update(const PackageNameInput & input)
{
  PackageNameOutput output{};
  output.output_hoge_msg.data.resize(2);
  output.output_hoge_msg.data.at(0) = 1.0f;
  output.output_hoge_msg.data.at(1) = input.input_hoge_msg->data.at(0);
  return output;
}

}  // namespace package_name
