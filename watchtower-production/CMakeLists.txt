#Root CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project (Watchtower)

# Set global C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set the runtime library for the entire project
if(WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

# Include packages
#include_directories(${CMAKE_SOURCE_DIR}/../modules/mosquitto/include)

# Add the Mosquitto submodule (If MQTT is needed)
#add_subdirectory(${CMAKE_SOURCE_DIR}/../modules/mosquitto ${CMAKE_BINARY_DIR}/mosquitto)

# Add the main executable
add_executable( # User interface
    WatchtowerProgram ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# Link the Mosquitto library
#target_link_libraries(WatchtowerProgram mosquitto)

# Include targeted directories for the program libraries
target_include_directories(WatchtowerProgram PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Set the output directory for the executable
set_target_properties(WatchtowerProgram PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

