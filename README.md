# opengl-introduction
Set of classes which abstract OpenGL fundamentals

# Overview
The abstractions here allow for the easy creation of a window with a camera, the addition and transformation of objects loaded from obj files within that scene, and the loading and using of shaders to be applied to the objects. The application of this is very limited and was mainly created to demonstrate the minimal OpenGL I have learnt over the past fortnight.

# Window
The window is instantiated with the use of the GLFW library. The boiler-plate initialisation code is also hidden away in the Window class. A struct which defines all the data necessary for the camera object is also stored in the Window class and the movement of the camera from keyboard input is handled within the class too.

# Camera
The camera uses a perspective projection and has 4 attributes: position, direction, pitch, and yaw. The camera can be moved up, down, forwards (in the direction of travel), backwards (against the direction of travel), left, and right.

# Models
Models are loaded from a .obj file but must be in a particular format. There must be no texture coordinates and all faces must be triangulated. There is no support for vertex indexing so the vertex attributes (positions and normals) are unpacked before they are loaded using OpenGL. Models have an individual model matrix and can be rotated or translated relative to their model position. They are drawn by passing in the projection matrix and the shader to use.

# Shader
The Shader class allows the loading of a vertex fragment pair from two separate files. These are bound and can be used at a later time by calling shader.use(). It is also easy to set the uniform values for a shader by using the templated functions.
