#include <GL/glut.h>
#include <iostream>
#ifndef __MATRIX_H__
#define __MATRIX_H__
class Matrix3D {
private:
    float mat[9] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
public:
	Matrix3D() {}
    Matrix3D(float *matBase) {
        for (int i = 0; i < sizeof(this->mat); i++) {
            mat[i] = &(matBase + i);
        }
    }
};
#endif
