# telemetry_src/CMakelists.txt

# Create executable
add_executable(WatchtowerTelemetryProgram mainTelemetry.cpp)

# Include shared source libraries
#include_directories(${CMAKE_SOURCE_DIR}/shared_libraries)
target_include_directories(WatchtowerTelemetryProgram PUBLIC ${CMAKE_SOURCE_DIR}/shared_libraries)