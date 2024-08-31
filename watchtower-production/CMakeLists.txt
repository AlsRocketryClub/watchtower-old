#Root CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project (Watchtower)

# Set global C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set the runtime library for the entire project
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Force Google Test to use the shared runtime library
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Include packages
#add_subdirectory(../modules/googletest googletest)
#include(GoogleTest) # Include GoogleTest
#include(CTest) # Enable testing and create configuration file
#include_directories(${CMAKE_SOURCE_DIR}/../modules/paho.mqtt.cpp/include)
#include_directories(${CMAKE_SOURCE_DIR}/../modules/paho.mqtt.c/src)
# set(PahoMqttCpp_DIR ${CMAKE_SOURCE_DIR}/../modules/paho.mqtt.cpp/cmake/PahoMqttCppConfig.cmake.in)
include_directories(${CMAKE_SOURCE_DIR}/../modules/mosquitto/include)
# find_package(PahoMqttCpp REQUIRED)    

# Detect the operating system to set the threading options based on the OS
if(WIN32)
    # Windows-specific settings
    set(WITH_THREADING "ON" CACHE BOOL "Enable threading support")
    set(WITH_PTHREAD "OFF" CACHE BOOL "Disable pthread support")
elseif(UNIX)
    # Unix-specific settings
    set(WITH_THREADING "ON" CACHE BOOL "Enable threading support")
    set(WITH_PTHREAD "ON" CACHE BOOL "Enable pthread support")
endif()

# Add the Mosquitto submodule
add_subdirectory(${CMAKE_SOURCE_DIR}/../modules/mosquitto ${CMAKE_BINARY_DIR}/mosquitto)

# Add the Paho MQTT C submodule
#add_subdirectory(${CMAKE_SOURCE_DIR}/../modules/paho.mqtt.c ${CMAKE_BINARY_DIR}/paho.mqtt.c)

# Include the Paho MQTT C headers
#include_directories(${CMAKE_SOURCE_DIR}/../modules/paho.mqtt.c/src)

# Link the Paho MQTT C libraries
# add_library(paho-mqtt3a SHARED IMPORTED)
# set_target_properties(paho-mqtt3a PROPERTIES 
#     IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../modules/paho.mqtt.c/build/src/Debug/paho-mqtt3a.dll
#     IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/../modules/paho.mqtt.c/build/src/Debug/paho-mqtt3a.lib
# )

# add_library(paho-mqtt3c SHARED IMPORTED)
# set_target_properties(paho-mqtt3c PROPERTIES 
#     IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../modules/paho.mqtt.c/build/src/Debug/paho-mqtt3c.dll
#     IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/../modules/paho.mqtt.c/build/src/Debug/paho-mqtt3c.lib
# )

# Set the installation prefix for the eclipse-paho-mqtt-c library
#set(eclipse-paho-mqtt-c_DIR ${CMAKE_SOURCE_DIR}/../modules/paho.mqtt.c/build/src/Debug)

# Set the eclipse-paho-mqtt-c_DIR to the directory containing the configuration files
#set(eclipse-paho-mqtt-c_DIR ${CMAKE_SOURCE_DIR}/../modules/paho.mqtt.c/build/src)
# Find the package
#find_package(eclipse-paho-mqtt-c REQUIRED)

# Add the Paho MQTT C++ submodule
#add_subdirectory(${CMAKE_SOURCE_DIR}/../modules/paho.mqtt.cpp ${CMAKE_BINARY_DIR}/paho.mqtt.cpp)

# Set the CMAKE_PREFIX_PATH to include the directory where eclipse-paho-mqtt-c is built
#set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/paho.mqtt.c)




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
add_executable( # User interface
    WatchtowerCommandProgram ${CMAKE_SOURCE_DIR}/command_src/mainCommand.cpp
)

# Link the Mosquitto library
#target_link_libraries(WatchtowerComputeProgram mosquitto)
#target_link_libraries(WatchtowerTelemetryProgram mosquitto)
target_link_libraries(WatchtowerConsoleProgram mosquitto)
target_link_libraries(WatchtowerCommandProgram mosquitto)

# Link against the Paho MQTT C++ library
#target_link_libraries(WatchtowerComputeProgram paho-mqttpp3)
#target_link_libraries(WatchtowerTelemetryProgram paho-mqttpp3)
#target_link_libraries(WatchtowerConsoleProgram paho-mqttpp3-static paho-mqtt3as-static)
#target_link_libraries(WatchtowerCommandProgram paho-mqttpp3-static paho-mqtt3as-static)

# Include targeted directories for the program libraries
# target_include_directories(WatchtowerComputeProgram PUBLIC ${CMAKE_SOURCE_DIR}/shared_libraries)
# target_include_directories(WatchtowerTelemetryProgram PUBLIC ${CMAKE_SOURCE_DIR}/shared_libraries)
target_include_directories(WatchtowerConsoleProgram PUBLIC ${CMAKE_SOURCE_DIR}/shared_libraries)
target_include_directories(WatchtowerCommandProgram PUBLIC ${CMAKE_SOURCE_DIR}/shared_libraries)

# Link against the Paho MQTT C++ library
#target_link_libraries(WatchtowerComputeProgram paho-mqttpp3)