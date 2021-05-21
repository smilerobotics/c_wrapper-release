#include "c_wrapper_ros2/c_wrapper_ros2.h"
#include "rclcpp/rclcpp.hpp"

void ros2_init(int argc, char **argv)
{
    rclcpp::init(argc, argv);
}

void ros2_shutdown()
{
    rclcpp::shutdown();
}
