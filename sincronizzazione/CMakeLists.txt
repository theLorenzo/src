cmake_minimum_required(VERSION 2.8.3)
project(sincronizzazione)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS geometry_msgs message_filters robotics_hw1 roscpp rospy std_msgs)

## Declare a catkin package
catkin_package( CATKIN_DEPENDS geometry_msgs message_filters robotics_hw1 std_msgs)

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(sincronizzazione src/sincronizzatore.cpp)
target_link_libraries(sincronizzazione ${catkin_LIBRARIES})

