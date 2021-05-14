cmake_minimum_required(VERSION 2.8.3)
project(rviz_publishing)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs tf tf2 tf2_ros rospy turtlesim)


## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})


add_executable(rviz_publisher src/rviz_publisher.cpp)
target_link_libraries(rviz_publisher ${catkin_LIBRARIES})



add_executable(rviz_publisher_scoutodom src/rviz_publisher_scoutodom.cpp)
target_link_libraries(rviz_publisher_scoutodom ${catkin_LIBRARIES})


add_executable(rviz_publisher_gtpose src/rviz_publisher_gtpose.cpp)
target_link_libraries(rviz_publisher_gtpose ${catkin_LIBRARIES})
