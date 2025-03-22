cmake_minimum_required(VERSION 3.25)
project(PYTHML)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

set(CMAKE_CXX_COMPILER g++)

include_directories(${Python3_INCLUDE_DIRS} include) 

set(SOURCES
    src/main.cpp
    src/parser.cpp
)

add_executable(PYTHML ${SOURCES})

target_link_libraries(PYTHML ${Python3_LIBRARIES})

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
