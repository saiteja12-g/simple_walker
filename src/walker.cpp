/**
 * @file walker.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>

using std::placeholders::_1;
using namespace std::chrono_literals;

using LASER_SCAN = sensor_msgs::msg::LaserScan;
using TWIST = geometry_msgs::msg::Twist;

class Walker : public rclcpp::Node {
 public:
    Walker() : Node("simple_walker") {
        auto callback = std::bind(&Walker::laserData_callback, this, _1);
        laser_data_sub =
            this->create_subscription<LASER_SCAN>("scan", 10, callback);
        publish_velocity = this->create_publisher<TWIST>("cmd_vel", 10);
    }

 private:
  void laserData_callback(const LASER_SCAN& scanData) {
    if (scanData.header.stamp.sec == 0) {
      return;
    }

    auto laser_scan_data = scanData.ranges;
    for (int i = 330; i < 330 + 60; i++) {
      if (laser_scan_data[i % 360] < 0.8) {
        move_bot(0.0, 0.1);
      } else {
        move_bot(0.1, 0.0);
      }
    }
  }

  void move_bot(float x_velocity, float z_velocity) {
    auto velocity_msg = TWIST();
    velocity_msg.linear.x = x_velocity;
    velocity_msg.angular.z = -z_velocity;
    publish_velocity->publish(velocity_msg);
  }

  // Declaring the private variables
  rclcpp::Subscription<LASER_SCAN>::SharedPtr laser_data_sub;
  rclcpp::Publisher<TWIST>::SharedPtr publish_velocity;
  rclcpp::TimerBase::SharedPtr timer;
  LASER_SCAN last_scan_data;
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Walker>());
  rclcpp::shutdown();
  return 0;
}
