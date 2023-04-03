cmake_minimum_required(VERSION 3.17)

project(cgame)

add_executable(
    ${PROJECT_NAME} 
    app/src/main.cpp
    app/src/draw.cpp
)

target_link_libraries(${PROJECT_NAME} GL glfw GLEW)