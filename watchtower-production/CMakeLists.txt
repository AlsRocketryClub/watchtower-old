#Root CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project (Watchtower)

# Set the runtime library for the entire project
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Force Google Test to use the shared runtime library
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add the Google Test subdirectory
add_subdirectory(../modules/googletest googletest)

# Enable testing
enable_testing()

# Add the various subdirectories
add_subdirectory(src)
add_subdirectory(test)

# Assume that your test executable is named 'test_example'
add_test(NAME example_test COMMAND test_example)