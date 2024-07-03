# OpenGL Real-Time Raytracing

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

![perspecive projection](https://github.com/Bozmoss/CourseWork/blob/master/README-resources/perspectiveProjection.png?raw=true)

Fig. 1

Going about calculating this is surprisingly simple. Let a point A in 3D space be defined as the co-ordinate ![(x, y, z)](https://latex.codecogs.com/svg.image?(x,y,z)), and A’ be the projection of A with altered ![x](https://latex.codecogs.com/svg.image?x) and ![y](https://latex.codecogs.com/svg.image?y) values, and ![z=0](https://latex.codecogs.com/svg.image?z=0). Let CAM be the position of the camera defined as ![(0, 0, -DEPTH)](https://latex.codecogs.com/svg.image?(0,0,-DEPTH)), where DEPTH is the distance between the camera and the screen, and let C be the point where CAM is normal to the screen. Looking top down so the only factor being changed is ![equation](https://latex.codecogs.com/svg.image?x), we get Fig. 2

![perspecive explain 1](https://github.com/Bozmoss/CourseWork/blob/master/README-resources/perspectiveExplain1.jpg?raw=true)

Fig. 2

The length of AB will be ![x](https://latex.codecogs.com/svg.image?x), the length of CAM to C will be DEPTH, and the length of CB will be ![z](https://latex.codecogs.com/svg.image?z), and the angles at B and C will be right angles.This leads to two similar triangles which can be seen in Fig. 3, and the same logic can be applied for the y direction.

![perspecive explain 2](https://github.com/Bozmoss/CourseWork/blob/master/README-resources/perspectiveExplain2.jpg?raw=true)

Fig. 3

This gives that the equation of a projected coordinate from 3D space to ![z=0](https://latex.codecogs.com/svg.image?z=0) is

![A'=(\frac{x\cdot DEPTH}{z+DEPTH},\frac{y\cdot DEPTH}{z+DEPTH},0)](https://latex.codecogs.com/svg.image?A'=(%5Cfrac%7Bx%5Ccdot%20DEPTH%7D%7Bz&plus;DEPTH%7D,%5Cfrac%7By%5Ccdot%20DEPTH%7D%7Bz&plus;DEPTH%7D,0))

This can be applied to a code extract shown in OpenGL:
```C++
Vertex Vertex::getProejctedVertex() {
    return Vertex(FOV * (x) / (FOV + z), FOV * (y) / (FOV + z), 0);
}
```

Here, Vertex is a class with Vertex attributes and the getProjectedVertex() method returns a new Vertex with properties from the previously derived equation. Simply applying this with some rotation matrices gives these results:

![GL 1](https://github.com/Bozmoss/CourseWork/blob/master/README-resources/GL1.png?raw=true)

![GL 2](https://github.com/Bozmoss/CourseWork/blob/master/README-resources/GL2.png?raw=true)

So, as we can see depth, the perspective projection is working.

To rotate these projections would require the use of affine matrices, which can handle rotations and translations, and are as follows:

![mat1](https://latex.codecogs.com/svg.image?R_%7Bx%7D(%5Ctheta)=%5Cbegin%7Bbmatrix%7D&1&0&0&0%5C%5C&0&cos(%5Ctheta)&-sin(%5Ctheta)&0%5C%5C&0&sin(%5Ctheta)&cos(%5Ctheta)&0%5C%5C&0&0&0&1%5C%5C%5Cend%7Bbmatrix%7D)

![mat2](https://latex.codecogs.com/svg.image?R_%7By%7D(%5Ctheta)=%5Cbegin%7Bbmatrix%7D&cos(%5Ctheta)&0&sin(%5Ctheta)&0%5C%5C&0&1&0&0%5C%5C&-sin(%5Ctheta)&0&cos(%5Ctheta)&0%5C%5C&0&0&0&1%5C%5C%5Cend%7Bbmatrix%7D)

![mat3](https://latex.codecogs.com/svg.image?R_%7Bz%7D(%5Ctheta)=%5Cbegin%7Bbmatrix%7D&cos(%5Ctheta)&-sin(%5Ctheta)&0&0%5C%5C&sin(%5Ctheta)&cos(%5Ctheta)&0&0%5C%5C&0&0&1&0%5C%5C&0&0&0&1%5C%5C%5Cend%7Bbmatrix%7D)

These can be implemented into an affine matrix class with an example header class as follows:

```C++
#pragma once
#include <vector>
#include <cmath>

class AffineMatrix {
private:
    std::vector<std::vector<double>> mat;
public:
    AffineMatrix();
    virtual void scale(double scalar);
    virtual AffineMatrix add(AffineMatrix m);
    virtual AffineMatrix multiply(AffineMatrix m);
    virtual AffineMatrix inverse();
    virtual double atPos(int r, int c);
};
```

However, this method is very memory inefficient, as the inverse of each transform and rotation matrix needs to be applied to the position of CAM every frame, so in practice this method was found to be not the best. Instead, I started to do research on Signed Distance Functions (SDFs).

## Signed Distance Function (SDF) Rendering

### Research

I discovered signed distance functions (also known as signed distance fields) when researching how to add lighting to my scene and found that they were incredibly more efficient than reducing a shape to triangles. From my research, I discovered that to render a signed distance function, you need to ray march across every pixel on the screen, so I conducted further research to find an efficient way of doing this and settled on using a fragment shader, programmed in GLSL (GL Shader Language). Due to the way I am doing this, I also had to do research on vertex shaders and buffers using GLEW (GL Extension Wrangler) and GLFW (GL Framework).

### Application

How an SDF works is by defining a 2D or 3D shape as a function, and returning positive if a set point is inside the shape, or negative if it is outside. For example, the equation for a sphere in cartesian co-ordinates is:

![\sqrt{x^{2}+y^{2}+z^{2}}](https://latex.codecogs.com/svg.image?%5Csqrt%7Bx%5E%7B2%7D&plus;y%5E%7B2%7D&plus;z%5E%7B2%7D%7D)

Which, in terms of a position vector ![\vec{p}](https://latex.codecogs.com/svg.image?%5Cvec%7Bp%7D) is

![\left\|\vec{p}\right\|](https://latex.codecogs.com/svg.image?%5Cleft%5C%7C%5Cvec%7Bp%7D%5Cright%5C%7C)

Therefore, letting ![r](https://latex.codecogs.com/svg.image?r) be the radius of the sphere, if ![\left\|\vec{p}\right\|-r<0](https://latex.codecogs.com/svg.image?%5Cleft%5C%7C%5Cvec%7Bp%7D%5Cright%5C%7C-r%3C0), the point is outside the circle, but if ![\left\|\vec{p}\right\|-r>0](https://latex.codecogs.com/svg.image?%5Cleft%5C%7C%5Cvec%7Bp%7D%5Cright%5C%7C-r%3E0), the point is inside the circle. In GLSL, this can be written as:

```GLSL
float sphereSDF(vec3 p, vec3 c, float r) {
    return length(c-p) - r;
}
```

Where c is the centre, p is a point and r is the radius.
