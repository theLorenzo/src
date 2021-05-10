cmake_minimum_required(VERSION 2.8.3)
project(baseline)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs tf  robotics_hw1 geometry_msgs message_filters)

## Declare a catkin package
catkin_package(CATKIN_DEPENDS roscpp std_msgs robotics_hw1 tf  geometry_msgs nav_msgs message_filters)


## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})


add_executable(baseline src/gen_baseline.cpp)
target_link_libraries(baseline ${catkin_LIBRARIES})


add_executable(baseline_gtpose src/gen_baseline_gtpose.cpp)
target_link_libraries(baseline_gtpose ${catkin_LIBRARIES})

