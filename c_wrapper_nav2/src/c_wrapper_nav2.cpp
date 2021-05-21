#include "c_wrapper_nav2/nav2_client.hpp"
#include "c_wrapper_nav2/c_wrapper_nav2.h"

std::shared_ptr<c_wrapper_nav2::Nav2Client> g_nav_client;

void nav2_init()
{
    if (!g_nav_client)
    {
        rclcpp::NodeOptions option;
        g_nav_client = std::make_shared<c_wrapper_nav2::Nav2Client>(option);
    }
}

void nav2_send_goal(const double x, const double y, const double theta)
{
    g_nav_client->send_goal(x, y, theta);
    rclcpp::spin_some(g_nav_client);
}

int nav2_is_succeeded()
{
    if (g_nav_client->is_succeeded())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
