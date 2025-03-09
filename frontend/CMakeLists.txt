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

# Set default build type to Debug, but Release can also be specified when building
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

# Set Debug flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

# Set Release flags (optimizations and no debug symbols)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
