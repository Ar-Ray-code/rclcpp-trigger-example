# rclcpp-trigger-example

Setting wait points for example program by ROS2.

![](./image_for_readme/waittpoint_readme.png)

> **Warning**
>
> It is not recommended to use rclcpp without inheritance

<br>

## Run example

```bash
# Download and compile
git clone https://github.com/Ar-Ray-code/rclcpp-trigger-example.git
cd rclcpp-trigger-example/
colcon build

# run
./install/rclcpp_trigger/lib/rclcpp_trigger/trigger_example
```

### Send Trigger
```bash
ros2 topic pub --once /signal1 std_msgs/msg/Empty {}
ros2 topic pub --once /signal2 std_msgs/msg/Empty {}
```

<br>

## Example program

See [trigger_example.cpp](./src/trigger_example.cpp) .

```C++
#include "rclcpp_trigger/trigger.hpp"

int main(void)
{
    rclcpp::init(0, nullptr);
    rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("trigger_example");

    // Define only (trigger)
    Trigger trigger2(node, "signal2");

    // Define and running Trigger
    Trigger trigger1(node, "signal1", 10, true);
    std::cout << "Step1" << std::endl;

    trigger2.wait_until_callback();
    std::cout << "Step2" << std::endl;

    rclcpp::shutdown();
    return 0;
}
```