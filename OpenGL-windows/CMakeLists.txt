cmake_minimum_required(VERSION 3.10)
project(OpenGLTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(OpenGLTest src/main.cpp)

include_directories(include)

if (WIN32)
    target_link_libraries(OpenGLTest, glfw3 glew32 opengl32)
else()
    target_link_libraries(OpenGLTest, glfw, GLEW, GL)
endif()

link_directories(${CMAKE_SOURCE_DIR}/lib/glfw-3.4)
link_directories(${CMAKE_SOURCE_DIR}/lib/glew-2.1.0)