# src/CMakelists.txt
# Add source files
add_library(
    Watchtower main.cpp 
    userInterfaceLayer.cpp
    threadHandler.cpp
)

# Specify include directories for the library
#include_directories(${CMAKE_SOURCE_DIR}/include)
target_include_directories(Watchtower PUBLIC ${CMAKE_SOURCE_DIR}/include)
