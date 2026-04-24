cmake_minimum_required(VERSION 3.10)
project(SolarSystem)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

link_directories(lib)

file(GLOB_RECURSE SRC_FILES
    src/*.cpp
    src/*.c
)

add_executable(SolarSystem ${SRC_FILES})

target_link_libraries(SolarSystem
    glfw3
    opengl32
    gdi32
)