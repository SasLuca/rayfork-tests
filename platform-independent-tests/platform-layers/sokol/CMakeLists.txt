cmake_minimum_required(VERSION 3.1)
set(CMAKE_C_STANDARD 99)

add_library(sokol-platform-layer)
target_sources(sokol-platform-layer PRIVATE sokol_main.c glad/glad.c)
target_include_directories(sokol-platform-layer PUBLIC "${rayfork_path}" "${platform_header_path}" "sokol" ".")