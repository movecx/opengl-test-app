cmake_minimum_required(VERSION 3.10)

project(OpenGLTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

add_executable(OpenGLTest main.cpp)

target_link_libraries(OpenGLTest ${OPENGL_LIBRARIES} GLEW::GLEW glfw)