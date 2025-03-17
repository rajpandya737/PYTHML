cmake_minimum_required(VERSION 3.25)
project(frontend)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

set(CMAKE_CXX_COMPILER g++)

include_directories(${Python3_INCLUDE_DIRS} include) 

set(SOURCES
    src/main.cpp
    src/lexer.cpp
)

add_executable(frontend ${SOURCES})

target_link_libraries(frontend ${Python3_LIBRARIES})

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
