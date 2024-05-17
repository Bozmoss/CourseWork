#pragma once
#include <vector>
#include <iostream>
#include "Vertex.h"
using namespace std;
class Shape {
private:
    std::vector<std::vector<Vertex>> sides;
    std::vector<Vertex> sideCentres;
    virtual void checkSides();
public:
    Shape(Vertex* vArr, int len, int innerLen) {
        for (int i = 0, n = 0; i < len; i++) {
            std::vector<Vertex>* side = new std::vector<Vertex>;
            for (int j = 0; j < innerLen; j++, n++) {
                (*side).push_back(*(vArr + n));
            }
            sides.push_back(*side);
            delete side;
            side = nullptr;
        }
    }
    virtual void draw();
    virtual void rotate(float ax, float ay);
};