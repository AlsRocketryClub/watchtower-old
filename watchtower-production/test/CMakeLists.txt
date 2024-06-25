# test/CMakeLists.txt
# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
#include_directories(${PROJECT_SOURCE_DIR}/src)

# Add test files
#add_executable(test_example test_example.cpp)
add_executable(test_command test_command.cpp)

# Link the Google Test framework
target_link_libraries(test_command gtest gtest_command Watchtower)

# Discover tests (not working)
#gtest_discover_tests(
    #test_command
    #test_example
    #)

# Add tests from the main executable
add_test(NAME ProcessListenTest COMMAND test_command)
