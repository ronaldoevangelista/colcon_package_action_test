// Copyright (c) 2023, Ronaldo Evangelista
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "colcon_package_action_test/lambda.hpp"

#include <gtest/gtest.h>

#include <chrono>
#include <memory>

class MinimalPublisherTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    rclcpp::init(0, nullptr);
    node_ = std::make_shared<MinimalPublisher>();
  }

  void TearDown() override
  {
    rclcpp::shutdown();
  }

  std::shared_ptr<MinimalPublisher> node_;
};

TEST_F(MinimalPublisherTest, TestPublish) {
  auto subscription = node_->create_subscription<std_msgs::msg::String>(
    "topic",
    10,
    [](const std_msgs::msg::String::SharedPtr msg) {
      EXPECT_EQ(msg->data, "Hello, world! 0");
    });

  auto start_time = std::chrono::steady_clock::now();
  while (std::chrono::steady_clock::now() - start_time < std::chrono::seconds(1)) {
    rclcpp::spin_some(node_);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  EXPECT_GT(node_->getCount(), 0u);
}

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
