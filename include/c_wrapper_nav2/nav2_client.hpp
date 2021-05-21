#pragma once

#include "nav2_msgs/action/navigate_to_pose.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

namespace c_wrapper_nav2
{
    class Nav2Client : public rclcpp::Node
    {
    public:
        using NavigateToPose = nav2_msgs::action::NavigateToPose;
        using GoalHandleNavigateToPose = rclcpp_action::ClientGoalHandle<NavigateToPose>;

        explicit Nav2Client(const rclcpp::NodeOptions &options);
        void send_goal(double x, double y, double theta);
        bool is_succeeded() const
        {
            return m_is_succeeded;
        };

    private:
        rclcpp_action::Client<NavigateToPose>::SharedPtr client_ptr_;
        bool m_is_succeeded;

        void goal_response_callback(std::shared_future<GoalHandleNavigateToPose::SharedPtr> future);
        void feedback_callback(
            GoalHandleNavigateToPose::SharedPtr,
            const std::shared_ptr<const NavigateToPose::Feedback> feedback);
        void result_callback(const GoalHandleNavigateToPose::WrappedResult &result);
    };

} // namespace nav2_client
