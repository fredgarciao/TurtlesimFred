cmake_minimum_required(VERSION 2.8.3)
project(turtlesimfred)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES bir_challenges
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(gotogoal src/gotogoal.cpp)
target_link_libraries(gotogoal ${catkin_LIBRARIES})
