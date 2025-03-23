cmake_minimum_required(VERSION 3.25)
project(pythml)

# Find Python3
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Find Tidy (Ensure it finds static version)
find_package(PkgConfig REQUIRED)
pkg_check_modules(TIDY REQUIRED tidy)

set(CMAKE_CXX_COMPILER g++)

include_directories(${Python3_INCLUDE_DIRS} ${TIDY_INCLUDE_DIRS} include)

# Ensure static linking by directly specifying the static library file
set(TIDY_STATIC_LIB ${TIDY_LIBRARY_DIRS}/libtidy.a)

set(SOURCES
    src/main.cpp
    src/parser.cpp
    src/file.cpp
    src/runner.cpp
    src/format.cpp
)

add_executable(pythml ${SOURCES})

# Force static linking
target_link_libraries(pythml ${Python3_LIBRARIES} ${TIDY_STATIC_LIB})

# Set build type
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

# Set compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Ensure CMake prefers static libraries
set(CMAKE_FIND_LIBRARY_SUFFIXES .a)  # Prioritize .a over .so/.dll
set(CMAKE_EXE_LINKER_FLAGS "-static")  # Force static linking
