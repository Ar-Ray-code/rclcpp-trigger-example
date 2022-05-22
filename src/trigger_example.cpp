#include "rclcpp_trigger/trigger.hpp"

int main(void)
{
    rclcpp::init(0, nullptr);
    rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("trigger_example");

    Trigger trigger1(node, "signal2");

    Trigger trigger(node, "signal1", 10, true);
    std::cout << "Step1" << std::endl;

    trigger1.wait_until_callback();
    std::cout << "Step2" << std::endl;

    rclcpp::shutdown();
    return 0;
}