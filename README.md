# 2D Polygon Drawing and Affine Transformation with OpenGL

A C++ OpenGL application for drawing polygons and applying 2D affine transformations.

## Requirements

- MSYS2 MinGW64
- CMake 3.10+
- GLFW3, GLEW, GLM libraries

## Installation (MSYS2 MinGW64)

```bash
pacman -S mingw-w64-x86_64-glfw mingw-w64-x86_64-glew mingw-w64-x86_64-glm mingw-w64-x86_64-cmake
```

## Build

```bash
mkdir build && cd build
cmake ..
make
./polygon_lab.exe
```

## Controls

- **Left-click**: Add polygon point
- **Right-click**: Finish polygon (requires minimum 3 points)
- **L key**: Rotate counter-clockwise (1° per click)
- **R key**: Rotate clockwise (1° per click)
- **Arrow Keys**: Translate polygon (1 pixel per click)
- **< key**: Scale down (10% per click)
- **> key**: Scale up (10% per click)

## Features

- Draw custom polygons with mouse
- Visual feedback (red = selected, green = other, blue = drawing)
- Real-time affine transformations
- Multiple polygon support