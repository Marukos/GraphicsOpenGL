cmake_minimum_required(VERSION 3.21)
project(GraphicsOpenGL C)

set(CMAKE_C_STANDARD 99)

add_executable(GraphicsOpenGL main.c)
target_link_libraries(GraphicsOpenGL -lOpenGL32 -lfreeglut -lglu32)