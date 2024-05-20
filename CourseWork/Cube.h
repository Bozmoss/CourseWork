#pragma once
#include "Vertex.h"
#include "Shape.h"
class Cube {
private:
    Vertex cube[12][3] = {
        {
            Vertex(1, -1, 1),
            Vertex(1, -1, -1),
            Vertex(-1, -1, -1)
},
        {
            Vertex(1, -1, 1),
            Vertex(-1, -1, -1),
            Vertex(-1, -1, 1)
},
        {
            Vertex(1, 1, 1),
            Vertex(1, -1, 1),
            Vertex(-1, -1, 1)
},
        {
            Vertex(1, 1, 1),
            Vertex(-1, -1, 1),
            Vertex(-1, 1, 1)
},
        {
            Vertex(-1, 1, 1),
            Vertex(-1, -1, 1),
            Vertex(-1, -1, -1)
},
        {
            Vertex(-1, 1, 1),
            Vertex(-1, -1, -1),
            Vertex(-1, 1, -1)
},
        {
            Vertex(-1, 1, -1),
            Vertex(-1, -1, -1),
            Vertex(1, -1, -1)
},
        {
            Vertex(-1, 1, -1),
            Vertex(1, -1, -1),
            Vertex(1, 1, -1)
},
        {
            Vertex(1, 1, -1),
            Vertex(1, -1, -1),
            Vertex(1, -1, 1)
},
        {
            Vertex(1, 1, -1),
            Vertex(1, -1, 1),
            Vertex(1, 1, 1)
},
        {
            Vertex(1, 1, -1),
            Vertex(1, 1, 1),
            Vertex(-1, 1, 1)
},
        {
            Vertex(1, 1, -1),
            Vertex(-1, 1, 1),
            Vertex(-1, 1, -1)
}
    };
    Shape* s;
public:
    Cube(float cx = 0, float cy = 0, float cz = 0, float scalar = 1) {
        for (int i = 0; i < sizeof(cube) / sizeof(cube[0]); i++) {
            for (int j = 0; j < sizeof(cube[i]) / sizeof(cube[i][0]); j++) {
                cube[i][j].setX(scalar * (cube[i][j].getX()) + cx);
                cube[i][j].setY(scalar * (cube[i][j].getY()) + cy);
                cube[i][j].setZ(scalar * (cube[i][j].getZ()) + cz);
            }
        }
        Vertex* start = &cube[0][0];
        s = new Shape(start, sizeof(cube) / sizeof(cube[0]), sizeof(cube[0]) / sizeof(cube[0][0]));
    }
    virtual void draw(float ax, float ay);
};