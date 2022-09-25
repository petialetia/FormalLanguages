cmake_minimum_required(VERSION 3.10)

project(MinimalDFA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXECUTABLE_SUFFIX ".out")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -O2")

set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=undefined")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(test)