cmake_minimum_required(VERSION 3.25)
project(frontend)

# Find Python
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Set the C++ compiler
set(CMAKE_CXX_COMPILER g++)

# Include Python headers
include_directories(${Python3_INCLUDE_DIRS})

# Add the executable
add_executable(frontend src/main.cpp)

# Link the Python library
target_link_libraries(frontend ${Python3_LIBRARIES})
