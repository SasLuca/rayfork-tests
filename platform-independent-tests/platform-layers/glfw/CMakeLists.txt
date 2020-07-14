cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_STANDARD 99)

# Setup GLFW
add_compile_definitions(GLFW_INCLUDE_NONE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw EXCLUDE_FROM_ALL)

add_library(glfw-platform-layer main.c glad.c)