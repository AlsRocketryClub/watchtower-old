#Root CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project (Watchtower)

# Set global C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set the runtime library for the entire project
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Force Google Test to use the shared runtime library
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Include the GoogleTest and CTest
add_subdirectory(../modules/googletest googletest)
include(GoogleTest)
include(CTest) # Enable testing and create configuration file

# Enable testing
#enable_testing() # Deprecated due to CTest inclusion

# Add the various subdirectories
add_subdirectory(cpp_src)
#add_subdirectory(test)

# Assume that your test executable is named 'test_example'
# add_test(NAME example_test COMMAND test_example) # Deprecated due to gtest_discover_tests

# Include directories for the program libraries
#include_directories(${CMAKE_SOURCE_DIR}/include)

# Add an executable for the main program
#add_executable(Watchtower cpp_src/main.cpp)