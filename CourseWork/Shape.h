#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include "PVector.h"
using namespace std;
class Shape {
private:
    std::vector<std::vector<PVector>> sides;
    std::vector<PVector> normals;
    std::vector<float> camVecAngles;
    PVector transform = PVector(0, 0, 0);
    virtual void rotate(float ax, float ay);
    virtual void updateNormals();
    virtual void calculateSideClearance();
public:
    Shape(PVector* vArr, int len, int innerLen, float xoffset = 0, float yoffset = 0, float zoffset = 0) {
        transform = transform.transform(PVector(xoffset, yoffset, zoffset));
        for (int i = 0, n = 0; i < len; i++) {
            std::vector<PVector>* side = new std::vector<PVector>;
            for (int j = 0; j < innerLen; j++, n++) {
                side->push_back(*(vArr + n));
                if (j == 0) {
                    PVector v1 = PVector((*(vArr + n + 1)).getX() - (*(vArr + n)).getX(), (*(vArr + n + 1)).getY() - (*(vArr + n)).getY(), (*(vArr + n + 1)).getZ() - (*(vArr + n)).getZ());
                    PVector v2 = PVector((*(vArr + n + 2)).getX() - (*(vArr + n)).getX(), (*(vArr + n + 2)).getY() - (*(vArr + n)).getY(), (*(vArr + n + 2)).getZ() - (*(vArr + n)).getZ());
                    PVector cross = v1.crossProd(v2);
                    cross.scale(1 / cross.getMagnitude());
                    normals.push_back(cross.transform(transform));
                }
            }
            sides.push_back(*side);
            delete side;
            side = nullptr;
        }
    }
    virtual void draw(float ax, float ay);
};