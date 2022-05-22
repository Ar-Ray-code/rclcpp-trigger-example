cmake_minimum_required(VERSION 3.5)
project(rclcpp_trigger)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter -Werror -Wfatal-errors -Wno-unused-variable -Wno-unused-function)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

# picamera_pub_exec ======================================
ament_auto_add_executable(trigger_example src/trigger_example.cpp)
# ===================================================================

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package()