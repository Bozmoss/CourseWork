#include <GL/glut.h>
#include "Vertex.h"
#include <cmath>
#ifndef __VECTOR3_H__
#define __VECTOR3_H__
class Vector3 {
private:
    float vector[3];
public:
    Vector3(Vertex v1, Vertex v2) {
        vector[0] = v2.getX() - v1.getX();
        vector[1] = v2.getY() - v1.getY();
        vector[2] = v2.getZ() - v1.getZ();
    }
    Vector3(float *vStart) {
        for (int i = 0; i < sizeof(this->vector) / sizeof(this->vector[0]); i++) {
            vector[i] = *(vStart + i);
        }
    }
    virtual Vector3 crossProduct(Vector3 a);
    virtual float modulus();
    virtual Vector3 scale(float scalar);
    virtual float i();
    virtual float j();
    virtual float k();
};
#endif
