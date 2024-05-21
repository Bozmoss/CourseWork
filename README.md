Clone into vs code then open the CourseWork.vcxproji in CourseWork

File contents:

- Cube.h, Cube.cpp:
  Class that renders a cube in a set position on the screen, default is (0, 0, 0), with a scalar (default 1) that affects the side length

- DebugLines.h, DebugLines.cpp:
  Draws the lines in the positive x, y, and z directions to aid debugging

- GLOBAL.h:
  Stores the global variables used across multiple files

- Main.cpp:
  Main part of the code whcih runs the OpenGL environment

- PVector.h, PVector.cpp:
  Position vector class used for storing coordinate positions with vector methods, takes in an x, y, and z component with optional rgb components (default 1 1 1)

- Shape.cpp, Shape.h:
  Draws a 3D shape from a 2D array of PVectors, given the array's length and the length of the arrays in the 2D aray, with optional coordinate offsets to accomodate for side normals
