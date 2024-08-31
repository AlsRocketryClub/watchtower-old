cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(flash-led-example)
set(CMAKE_CXX_STANDARD 11)

add_executable(flash-led ./flash-led.cpp)
target_link_libraries(flash-led PUBLIC pigpio fmt)


