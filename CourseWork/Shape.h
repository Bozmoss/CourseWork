#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include "Vertex.h"
using namespace std;
class Shape {
private:
    std::vector<std::vector<Vertex>> sides;
    std::vector<Vertex> normals;
    std::vector<float> dotProds;
    virtual void rotate(float ax, float ay);
    virtual void updateNormals();
    virtual void updateDotProds();
public:
    Shape(Vertex* vArr, int len, int innerLen) {
        for (int i = 0, n = 0; i < len; i++) {
            std::vector<Vertex>* side = new std::vector<Vertex>;
            for (int j = 0; j < innerLen; j++, n++) {
                (*side).push_back(*(vArr + n));
                if (j == 0) {
                    Vertex v1 = Vertex((*(vArr + n + 1)).getX() - (*(vArr + n)).getX(), (*(vArr + n + 1)).getY() - (*(vArr + n)).getY(), (*(vArr + n + 1)).getZ() - (*(vArr + n)).getZ());
                    Vertex v2 = Vertex((*(vArr + n + 2)).getX() - (*(vArr + n)).getX(), (*(vArr + n + 2)).getY() - (*(vArr + n)).getY(), (*(vArr + n + 2)).getZ() - (*(vArr + n)).getZ());
                    Vertex cross = Vertex(v1.getY() * v2.getZ() - v1.getZ() * v2.getY(), v1.getZ() * v2.getX() - v1.getX() * v2.getZ(), v1.getX() * v2.getY() - v1.getY() * v2.getX());
                    normals.push_back(Vertex(cross.getX() / std::sqrt(cross.getX() * cross.getX() + cross.getY() * cross.getY() + cross.getZ() * cross.getZ()), 
                        cross.getY() / std::sqrt(cross.getX() * cross.getX() + cross.getY() * cross.getY() + cross.getZ() * cross.getZ()), 
                        cross.getZ() / std::sqrt(cross.getX() * cross.getX() + cross.getY() * cross.getY() + cross.getZ() * cross.getZ())));
                }
            }
            sides.push_back(*side);
            delete side;
            side = nullptr;
        }
    }
    virtual void draw(float ax, float ay);
};