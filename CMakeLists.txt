cmake_minimum_required(VERSION 3.10)
project(folgern)

# Build settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Stronger optimization for Release
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG -Wall -mtune=native")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

# Set default to Release if none given
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type selected, defaulting to Release")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build: Debug Release RelWithDebInfo MinSizeRel" FORCE)
endif()

add_library(folgern src/tensor.cpp)
target_include_directories(folgern PUBLIC src)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE folgern)
