cmake_minimum_required(VERSION 3.25)
project(pythml)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(PkgConfig REQUIRED)
pkg_check_modules(TIDY REQUIRED tidy)

set(CMAKE_CXX_COMPILER g++)

include_directories(${Python3_INCLUDE_DIRS} ${TIDY_INCLUDE_DIRS} include) 

# Explicitly point to the static library of tidy
set(TIDY_STATIC_LIB /usr/local/lib/libtidy.a)  # Update this path if necessary
link_directories(${TIDY_LIBRARY_DIRS})

set(SOURCES
    src/main.cpp
    src/parser.cpp
    src/file.cpp
    src/runner.cpp
    src/format.cpp
)

add_executable(pythml ${SOURCES})

# Link dynamically with Python3 and statically with tidy
target_link_libraries(pythml ${Python3_LIBRARIES} ${TIDY_STATIC_LIB})

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
