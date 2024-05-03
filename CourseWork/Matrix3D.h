#include <GL/glut.h>
#include <iostream>
#ifndef __MATRIX_H__
#define __MATRIX_H__
class Matrix3D {
private:
	float mat[3][3] = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} }; //Default identity
public:
	Matrix3D() {}
	Matrix3D(float mat[3][3]) {
		for (int i = 0; i < sizeof(this->mat); i++) {
			for (int j = 0; j < sizeof(this->mat[i]); j++) {
				this->mat[i][j] = mat[i][j];
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cout << this->mat[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
};
#endif
