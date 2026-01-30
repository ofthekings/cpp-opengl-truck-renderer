# 3D Truck Renderer (C++ / OpenGL)
Real-time 3D rendering application built in C++ using modern OpenGL.  
The program loads and renders a truck model exported from Blender (OBJ) and displays it in a 3D scene using a custom rendering pipeline.

#### Note: 
* All rendering, pipeline, shaders, and interaction code were implemented by me in C++ using OpenGL
* The OBJ was created in Blender by Nathan Wong.


## Features
* OpenGL rendering pipeline (VBO, EBO, VAO)
* GLSL vertex and fragment shaders
* View and projection matrices (GLM) for scene viewpoint definition
* OBJ model loading
* Wireframe rendering mode for geometry debugging
* Keyboard controls (WASD + QERF) to adjust the viewpoint in the 3D scene

## Preview
![Demo](truck.gif)

## Build / Run
This project was developed using C++ and OpenGL.

Dependencies:
* OpenGL
* GLM
* GLFW
* GLEW (or equivalent)
