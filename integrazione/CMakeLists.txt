cmake_minimum_required(VERSION 2.8.3)
project(integrazione)



## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs robotics_hw1 geometry_msgs message_filters dynamic_reconfigure)
  
generate_dynamic_reconfigure_options(
cfg/metodi.cfg
)  

## Declare a catkin package
catkin_package(CATKIN_DEPENDS roscpp std_msgs robotics_hw1 geometry_msgs nav_msgs message_filters dynamic_reconfigure)

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})


add_executable(integratore src/integratore.cpp)
target_link_libraries(integratore ${catkin_LIBRARIES})



