# src/CMakelists.txt
# Include header directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files
add_library(Watchtower example.cpp)