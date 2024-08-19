#Root CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project (Watchtower)

# Set global C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set the runtime library for the entire project
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Force Google Test to use the shared runtime library
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Include the GoogleTest, CTest
#add_subdirectory(../modules/googletest googletest)
#include(GoogleTest) # Include GoogleTest
#include(CTest) # Enable testing and create configuration file
include_directories(../modules/paho.mqtt.cpp/src)

# Enable testing
#enable_testing() # Deprecated due to CTest inclusion

# Add the various source subdirectories
#add_subdirectory(compute_src)
#add_subdirectory(telemetry_src)
#add_subdirectory(console_src)
#add_subdirectory(test)

# Assume that your test executable is named 'test_example'
# add_test(NAME example_test COMMAND test_example) # Deprecated due to gtest_discover_tests

# Add executables for all the programs
# add_executable( # Application that handles tracking and actuator control
#     WatchtowerComputeProgram ${CMAKE_SOURCE_DIR}/compute_src/mainCompute.cpp
# )
# add_executable( # Application that handles telemetry
#     WatchtowerTelemetryProgram ${CMAKE_SOURCE_DIR}/telemetry_src/mainTelemetry.cpp
# )
add_executable( # Application that handles the console interface with the user
    WatchtowerConsoleProgram ${CMAKE_SOURCE_DIR}/console_src/mainConsole.cpp
)
add_executable( # Application that handles the console interface with the user
    WatchtowerConsoleProgram ${CMAKE_SOURCE_DIR}/console_src/mainConsole.cpp
)

# Include targeted directories for the program libraries
# target_include_directories(WatchtowerComputeProgram PUBLIC ${CMAKE_SOURCE_DIR}/shared_libraries)
# target_include_directories(WatchtowerTelemetryProgram PUBLIC ${CMAKE_SOURCE_DIR}/shared_libraries)
target_include_directories(WatchtowerConsoleProgram PUBLIC ${CMAKE_SOURCE_DIR}/shared_libraries)

# Link against the Paho MQTT C++ library
#target_link_libraries(WatchtowerComputeProgram paho-mqttpp3)