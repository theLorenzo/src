cmake_minimum_required(VERSION 2.8.3)
project(service)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation)

add_service_files(
  FILES
  ResetZero.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

## Declare a catkin package
catkin_package(CATKIN_DEPENDS message_runtime)

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(reset_zero src/reset_zero.cpp)
target_link_libraries(reset_zero ${catkin_LIBRARIES})
add_dependencies(reset_zero ${catkin_EXPORTED_TARGETS})


add_executable(client src/client.cpp)
target_link_libraries(client ${catkin_LIBRARIES})
add_dependencies(client ${catkin_EXPORTED_TARGETS})

