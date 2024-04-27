cmake_minimum_required(VERSION 3.8)
project(MQTT_test)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
include_directories (${PROJECT_SOURCE_DIR}/include)

# 查找mosquitto包
# find_package(mosquitto REQUIRED)

# include_directories(${mosquitto_INCLUDE_DIRS})

# COMPILE  创建一个可执行文件
# add_executable(
#   ${PROJECT_NAME}
#   src/main.cpp
# )

# target_link_libraries(
#   ${PROJECT_NAME}
#   # ${mosquitto_LIBRARIES}
#   "/usr/lib/aarch64-linux-gnu/libmosquitto.so"
# )

add_executable(
  main2
  src/main2.cpp
  src/mosquitto_mqtt_util.cpp
)

target_link_libraries(
  main2
  "/usr/lib/aarch64-linux-gnu/libmosquitto.so"
)