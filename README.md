# OpenGL Real-TIme Raytracing

For my project, I am going to make a 3D raytracing engine, taking some inspiration from how blender deals with their rendering. When this project is completed, I want to have a 3D simulated environment in which objects can be added and different material properties of the object can be changed in real time, with some physics as well.

To achieve this, I would need to use graphics in such a way that they can be altered without using too much memory, and as I am dealing with graphics at a large realistic 3D level, it would be way more efficient to make use of the graphics card to handle rendering rather than normal memory. If I want the objects and their properties to be changed while the program is running, it would be wise to use an object-oriented approach. Some classes that I may use would include:
-	Buffer objects, to handle sending data to the graphics card.
-	Vertex objects, to handle where on the screen polygon vertices should be rendered.
-	Variable handling, to dynamically control and change variables, and communicating with the buffer objects.
-	GUI class, to handle user input data and communicate with the variable handling class(es).

## Reduction to Triangles

### Research

For this method I did some research on how to set up the OpenGL (Open Graphics Library) environment and how to use the GLUT (GL Utility Toolkit) library of OpenGL. I researched the methods glVertex3f() and glColor3f() and used them in a Position Vector class to render vertices of polygons, and researched affine matrix transformations, as affine matrices support more transformations than 3 by 3 matrices. I also researched different projection methods, namely perspective and orthographic, and settled for perspective as it gave a more realistic view of the screen from a distance.

### Application

My first thought for going about this would be to use an approach which would simplify a 3D shape into many triangles, which would have 3 vertices, and could be rendered and dynamically altered by joining up the vertices of the triangles. This would be achievable by representing each vertex as a position vector in 3D space, then applying a perspective projection to it, as shown in Fig. 1.
![perspecive projection](https://github.com/Bozmoss/CourseWork/blob/master/README-resources/perspectiveProjection.png?raw=true)Fig. 1

Going about calculating this is surprisingly simple. Let a point A in 3D space be defined as the coordinate ![equation](https://latex.codecogs.com/svg.image?(x,y,z))
