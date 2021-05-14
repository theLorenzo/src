cmake_minimum_required(VERSION 3.0.2)
project(generazione)



## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs robotics_hw1 geometry_msgs)

## Declare a catkin package
catkin_package(CATKIN_DEPENDS roscpp std_msgs robotics_hw1 geometry_msgs nav_msgs)

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})


add_executable(generazione src/generatore.cpp)
add_dependencies(generazione robotics_hw1_generate_messages_cpp)
target_link_libraries(generazione ${catkin_LIBRARIES})



