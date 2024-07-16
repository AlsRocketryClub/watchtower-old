# src/CMakelists.txt

# Add source files
#add_library(
#    Watchtower main.cpp threadHandler.cpp
    #userInterfaceLayer.cpp
#)

# Create executable
add_executable(WatchtowerProgram main.cpp threadHandler.cpp)

# Specify include directories for the library-
#include_directories(${CMAKE_SOURCE_DIR}/include)
#target_include_directories(WatchtowerProgram PUBLIC ${CMAKE_SOURCE_DIR}/include)