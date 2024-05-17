#pragma once
#include <vector>
#include <iostream>
#include "Vertex.h"
using namespace std;
class Shape {
private:
    std::vector<std::vector<Vertex>> sides;
    std::vector<Vertex> normals;
    virtual void checkSides();
public:
    Shape(Vertex* vArr, int len, int innerLen) {
        for (int i = 0, n = 0; i < len; i++) {
            std::vector<Vertex>* side = new std::vector<Vertex>;
            for (int j = 0; j < innerLen; j++, n++) {
                (*side).push_back(*(vArr + n));
                if (j == 0) {
                    Vertex v1 = Vertex((*(vArr + n + 1)).getX() - (*(vArr + n)).getX(), (*(vArr + n + 1)).getY() - (*(vArr + n)).getY(), (*(vArr + n + 1)).getZ() - (*(vArr + n)).getZ());
                    Vertex v2 = Vertex((*(vArr + n + 2)).getX() - (*(vArr + n)).getX(), (*(vArr + n + 2)).getY() - (*(vArr + n)).getY(), (*(vArr + n + 2)).getZ() - (*(vArr + n)).getZ());
                }
            }
            sides.push_back(*side);
            delete side;
            side = nullptr;
        }
    }
    virtual void draw();
    virtual void rotate(float ax, float ay);
};