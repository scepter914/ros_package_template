cmake_minimum_required(VERSION 3.0.2)
project(package_name)

add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
  diagnostic_updater # diag
  dynamic_reconfigure # dynamic_reconfigure
  roscpp
  std_msgs
)
# find_package(Boost REQUIRED)
# find_package(Eigen3 REQUIRED)

# dynamic_reconfigure
generate_dynamic_reconfigure_options(
  cfg/PackageName.cfg
)

catkin_package(
  INCLUDE_DIRS
    include
  CATKIN_DEPENDS
    std_msgs
    diagnostic_updater
    dynamic_reconfigure
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  # ${Boost_INCLUDE_DIRS}
  # ${EIGEN3_INCLUDE_DIRS}
)

# Target
## package_name_node
set(PACKAGE_NAME_NODE
  package_name_node
)

add_executable(${PACKAGE_NAME_NODE}
  src/${PACKAGE_NAME_NODE}/main.cpp
  src/${PACKAGE_NAME_NODE}/package_name.cpp
  src/${PACKAGE_NAME_NODE}/package_name_node.cpp
)

target_link_libraries(${PACKAGE_NAME_NODE}
  ${catkin_LIBRARIES}
  # ${Eigen3_LIBRARIES}
  # ${Boost_LIBRARIES}
)

add_dependencies(${PACKAGE_NAME_NODE}
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
  ${PROJECT_NAME}_gencfg # dynamic_reconfigure
)

# Install
## executables and libraries
install(
  TARGETS
    ${PACKAGE_NAME_NODE}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## project namespaced headers
install(DIRECTORY include/${PROJECT_NAME_NODE}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

## directories
install(
  DIRECTORY
    config
    launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
