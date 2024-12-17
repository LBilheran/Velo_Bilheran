cmake_minimum_required(VERSION 3.5)

project(Velo_Bilheran LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Velo_Bilheran main.cpp renderer.h renderer.cpp vertexarray.h vertexarray.cpp
    vertexbuffer.h vertexbuffer.cpp shader.h shader.cpp camera.cpp camera.h controls.cpp controls.h
fpscontrols.cpp fpscontrols.h navigationcontrols.cpp navigationcontrols.h object.cpp object.h
shader.cpp shader.h texture.cpp texture.h uvbuffer.cpp uvbuffer.h pointlight.cpp pointlight.h
spotlight.h spotlight.cpp)

target_link_libraries(Velo_Bilheran glfw GLEW libGLEW.so libGLU.so libGL.so)

