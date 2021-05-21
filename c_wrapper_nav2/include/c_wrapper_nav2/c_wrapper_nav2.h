#pragma once

extern "C"
{
    void nav2_init();
    void nav2_send_goal(const double x, const double y, const double theta);
    int nav2_is_succeeded();
}