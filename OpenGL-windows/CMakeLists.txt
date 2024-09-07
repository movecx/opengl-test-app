cmake_minimum_required(VERSION 3.10)

project(OpenGLTest)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_GENERATOR_PLATFORM x64)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(SOURCES
    src/main.cpp
)

include_directories(
    lib/GLFW/include
    lib/GLEW/include
)

if(MSVC)
    set(GLFW_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/GLFW/lib-vc2022")
    set(GLEW_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/GLEW/lib/Release/x64")
else()
    message(FATAL_ERROR "MSVC is the only compiler supported.")
endif()

add_executable(OpenGLTest ${SOURCES})

target_link_libraries(OpenGLTest
    "${GLFW_LIB_DIR}/glfw3.lib"
    "${GLEW_LIB_DIR}/glew32s.lib"
    opengl32.lib
)

target_compile_definitions(OpenGLTest PRIVATE GLEW_STATIC)