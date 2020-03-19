cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_STANDARD 99)

add_executable(2d-camera-platformer
        main.c
        game.c
        ../dependencies/glad/glad.c)

target_link_libraries(2d-camera-platformer PRIVATE rayfork)