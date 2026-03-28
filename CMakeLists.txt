cmake_minimum_required(VERSION 3.10)
project(PolygonOpenGLLab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLFW3_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})

add_executable(polygon_lab main.cpp)

target_link_libraries(polygon_lab ${OPENGL_LIBRARIES} GLFW::glfw3 GLEW::GLEW)

if(MINGW)
    target_link_libraries(polygon_lab gdi32)
endif()