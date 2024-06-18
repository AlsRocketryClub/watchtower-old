#CMakeLists.txt
cmake_minimum_required(VERSION 3.0)

# Set the project name
project (ExampleProject)

# Add the Google Test subdirectory
add_subdirectory(modules/googletest)

# Add the test executable
add_executable(test_example test_example.cpp)

# Link the Google Test libraries to the test executable
target_link_libraries(test_example gtest gtest_main)