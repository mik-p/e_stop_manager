cmake_minimum_required(VERSION 3.5)
project(e_stop_propagators)
add_compile_options(-std=c++17)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  pluginlib
  actionlib
  move_base_msgs
  mbf_msgs
  mission_msgs
  record_msgs
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS
  roscpp
  pluginlib
  actionlib
  move_base_msgs
  mbf_msgs
  mission_msgs
  record_msgs
)

###########
## Build ##
###########
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

# add library and plugins library
add_library(${PROJECT_NAME}
  src/nav_propagator.cpp
  src/flex_nav_propagator.cpp
)
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)
add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
