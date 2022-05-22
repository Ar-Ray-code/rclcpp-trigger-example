#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/empty.hpp>
#include <rclcpp/qos.hpp>

class Trigger
{
public:
    Trigger(const rclcpp::Node::SharedPtr node , const std::string topic_name, const unsigned int depth_history = 10, const bool do_untile_callback = false)
    {
        this->wait_flag_ = true;
        this->wait_until_callback_is_running_ = false;
        this->node_ = node;
        this->topic_name_ = topic_name;
        this->depth_history_ = depth_history;
        if (do_untile_callback)
        {
            this->wait_until_callback();
        }
    }
    ~Trigger()
    {
        this->node_ = nullptr;
        if (this->wait_until_callback_is_running_)
        {
            this->signal_sub_ = nullptr;
        }
    }
    void wait_until_callback()
    {
        this->check_killed();
        this->signal_sub_ = this->node_->create_subscription<std_msgs::msg::Empty>(this->topic_name_, rclcpp::QoS(this->depth_history_), [this](std_msgs::msg::Empty::SharedPtr msg)
        {
            (void)msg;
            this->wait_flag_ = false;
        });
        if (this->wait_until_callback_is_running_)
        {
            std::cerr << "wait_until_callback() is already running" << std::endl;
            return;
        }
        // ---
        this->wait_until_callback_is_running_ = true;
        while (this->wait_flag_ && rclcpp::ok())
        {
            rclcpp::spin_some(this->node_);
        }
        this->check_killed();
    }
private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr signal_sub_;
    bool wait_flag_;
    bool wait_until_callback_is_running_;
    std::string topic_name_;
    unsigned int depth_history_;

    void check_killed()
    {
        if (!rclcpp::ok())
        {
            this->node_ = nullptr;
            exit(1);
        }
    }
};