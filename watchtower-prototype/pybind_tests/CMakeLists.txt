cmake_minimum_required(VERSION 3.13)
project(example)

set(CMAKE_CXX_STANDARD 14)

# Add the pybind11 subdirectory with an explicit binary directory
add_subdirectory(${CMAKE_SOURCE_DIR}/../../modules/pybind11 ${CMAKE_BINARY_DIR}/pybind11_build)

# Find Python interpreter and libraries from the virtual environment
set(Python_ROOT_DIR ${CMAKE_SOURCE_DIR}/../../venv)
set(Python_FIND_VIRTUALENV FIRST)

find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})
link_directories(${PYTHON_LIBRARIES})

# Create the Python module
add_library(example MODULE ${CMAKE_SOURCE_DIR}/src/example.cpp)

# Link pybind11 and Python libraries
target_link_libraries(example PRIVATE pybind11::module ${PYTHON_LIBRARIES})

# Set the output properties
set_target_properties(example PROPERTIES PREFIX "" SUFFIX ".pyd")
