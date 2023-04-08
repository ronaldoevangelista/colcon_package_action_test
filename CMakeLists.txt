cmake_minimum_required(VERSION 3.8)
project(colcon_package_action_test)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_compile_options(-Wno-sign-compare)


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rcutils)
find_package(sensor_msgs REQUIRED)

include_directories(include)
ament_export_include_directories("include/${PROJECT_NAME}")

add_executable(publisher_lambda src/lambda.cpp src/main.cpp)
ament_target_dependencies(publisher_lambda rclcpp std_msgs)

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
