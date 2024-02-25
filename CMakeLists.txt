cmake_minimum_required(VERSION 3.8)
project(colcon_package_action_test)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)

set(ignoreMe "${BUILD_DOCS}")
set(CGAL_DATA_DIR ".")
set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE TRUE)
set(OpenGL_GL_PREFERENCE "GLVND")

add_compile_options(-Wno-sign-compare)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rcutils)
find_package(sensor_msgs REQUIRED)

find_package(COLMAP REQUIRED)


message(STATUS  "---------------------------------------------")
get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
message(STATUS  "---------------------------------------------")

include_directories(
  include
  ${COLMAP_INCLUDE_DIRS}
)

link_directories(
  ${COLMAP_LINK_DIRS}
)

ament_export_include_directories("include/${PROJECT_NAME}")

message(STATUS  "AMENT_EXPORT_INCLUDE_DIRECTORIES")

message(STATUS  ${COLMAP_INCLUDE_DIRS})
message(STATUS  ${COLMAP_LINK_DIRS})
message(STATUS  ${COLMAP_LIBRARIES})

add_executable(publisher_lambda src/lambda.cpp src/main.cpp)
target_link_libraries(publisher_lambda ${COLMAP_LIBRARIES})

target_include_directories(publisher_lambda PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(
    publisher_lambda
    rclcpp
    std_msgs
    COLMAP
  )

install(TARGETS
  publisher_lambda
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)

  set(ament_cmake_copyright_FOUND TRUE)
  list(APPEND AMENT_LINT_AUTO_EXCLUDE ament_cmake_cpplint)

  find_package(ament_cmake_cpplint REQUIRED)
  ament_cpplint(MAX_LINE_LENGTH "120")
  ament_lint_auto_find_test_dependencies()

  ament_add_gtest(publisher_lambda_test test/lambda_test.cpp src/lambda.cpp)
  ament_target_dependencies(publisher_lambda_test rclcpp std_msgs)

endif()

ament_package()
