# test/CMakeLists.txt
# Include header directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add test files
add_executable(test_example
    test_example.cpp
    ${PROJECT_SOURCE_DIR}/src/example.cpp
)

# Link the Google Test framework
target_link_libraries(test_example gtest gtest_main Watchtower)