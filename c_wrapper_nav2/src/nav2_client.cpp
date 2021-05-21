#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>

#include "c_wrapper_nav2/nav2_client.hpp"
#include "rclcpp_components/register_node_macro.hpp"

namespace c_wrapper_nav2
{
    Nav2Client::Nav2Client(const rclcpp::NodeOptions &options)
        : Node("nav2_client", options)
    {
        printf("init1\n");
        this->client_ptr_ = rclcpp_action::create_client<NavigateToPose>(
            this,
            "navigate_to_pose");
        printf("init2\n");
        //this->timer_ = this->create_wall_timer(
        //std::chrono::milliseconds(500),
        //std::bind(&Nav2Client::send_goal, this));
    }

    void Nav2Client::send_goal(const double x, const double y, const double theta)
    {
        using namespace std::placeholders;
        //this->timer_->cancel();
        printf("hogehogeo\n");
        if (!this->client_ptr_->wait_for_action_server())
        {
            RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
            rclcpp::shutdown();
        }
        m_is_succeeded = false;

        auto goal_msg = NavigateToPose::Goal();
        goal_msg.pose.pose.position.x = x;
        goal_msg.pose.pose.position.y = y;
        // TODO: theta

        RCLCPP_INFO(this->get_logger(), "Sending goal");

        auto send_goal_options = rclcpp_action::Client<NavigateToPose>::SendGoalOptions();
        send_goal_options.goal_response_callback =
            std::bind(&Nav2Client::goal_response_callback, this, _1);
        send_goal_options.feedback_callback =
            std::bind(&Nav2Client::feedback_callback, this, _1, _2);
        send_goal_options.result_callback =
            std::bind(&Nav2Client::result_callback, this, _1);
        this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
    }

    void Nav2Client::goal_response_callback(std::shared_future<GoalHandleNavigateToPose::SharedPtr> future)
    {
        auto goal_handle = future.get();
        if (!goal_handle)
        {
            RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
        }
    }

    void Nav2Client::feedback_callback(
        GoalHandleNavigateToPose::SharedPtr,
        const std::shared_ptr<const NavigateToPose::Feedback> feedback)
    {
        (void)feedback;
        RCLCPP_INFO(this->get_logger(), "feedback");
    }

    void Nav2Client::result_callback(const GoalHandleNavigateToPose::WrappedResult &result)
    {
        switch (result.code)
        {
        case rclcpp_action::ResultCode::SUCCEEDED:
            m_is_succeeded = true;
            break;
        case rclcpp_action::ResultCode::ABORTED:
            RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
            return;
        case rclcpp_action::ResultCode::CANCELED:
            RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
            return;
        default:
            RCLCPP_ERROR(this->get_logger(), "Unknown result code");
            return;
        }
        std::stringstream ss;
        ss << "Result received: ";
        //ss << result.result->distance_remaining;
        RCLCPP_INFO(this->get_logger(), ss.str().c_str());
    }
} // namespace c_wrapper_nav2

RCLCPP_COMPONENTS_REGISTER_NODE(c_wrapper_nav2::Nav2Client)
