cmake_minimum_required(VERSION 3.10)
project(PolygonOpenGLLab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

# For GLFW3, use pkg-config as fallback
find_package(GLFW3 QUIET)
if(NOT GLFW3_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)
else()
    set(GLFW_LIBRARIES GLFW::glfw3)
endif()

# Include directories
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})

# Add executable
add_executable(polygon_lab main.cpp)

# Link libraries
target_link_libraries(polygon_lab 
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    GLEW::GLEW
)

# For MinGW, add additional flags
if(MINGW)
    target_link_libraries(polygon_lab gdi32)
endif()