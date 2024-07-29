# compute_src/CMakelists.txt

# Add source files
#add_library(
#    Watchtower mainCompute.cpp threadHandler.cpp
    #userInterfaceLayer.cpp
#)

# Create executable
add_executable(
    WatchtowerComputeProgram 
    mainCompute.cpp 
    threadHandler.cpp communicationLayer.cpp actuatorHandler.cpp)

# Include shared source libraries
#include_directories(${CMAKE_SOURCE_DIR}/shared_libraries)
target_include_directories(WatchtowerComputeProgram PUBLIC ${CMAKE_SOURCE_DIR}/shared_libraries)