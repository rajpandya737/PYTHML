cmake_minimum_required(VERSION 3.25)
project(PYTHML)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(PkgConfig REQUIRED)
pkg_check_modules(TIDY REQUIRED tidy)

set(CMAKE_CXX_COMPILER g++)

include_directories(${Python3_INCLUDE_DIRS} ${TIDY_INCLUDE_DIRS} include) 
link_directories(${TIDY_LIBRARY_DIRS})

set(SOURCES
    src/main.cpp
    src/parser.cpp
    src/file.cpp
    src/runner.cpp
    src/format.cpp
)

add_executable(PYTHML ${SOURCES})

target_link_libraries(PYTHML ${Python3_LIBRARIES} ${TIDY_LIBRARIES})

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
