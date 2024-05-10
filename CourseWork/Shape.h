#include <GL/glut.h>
#include <list>
#include "Vertex.h"
#include "Vector3.h"
#ifndef __SHAPE_H__
#define __SHAPE_H__
using namespace std;
class Shape {
private:
	list<list<Vertex>> sides;
    list<Vector3> normals;
	list<list<Vertex>>::iterator it1;
	list<Vertex>::iterator it2;
public:
	Shape(Vertex* vArr, int len, int innerLen) {
		for (int i = 0, n = 0; i < len; i++) {
			list<Vertex> sidesTemp;
			list<Vertex> edgesTemp;
			for (int j = 0; j < innerLen; j++, n++) {
				sidesTemp.push_back(*(vArr + n));
				if (j == 2) {
                    Vector3 v1(*(vArr + n - 2), *(vArr + n - 1));
                    Vector3 v2(*(vArr + n - 1), *(vArr + n));
                    Vector3 cross = v1.crossProduct(v2);
                    normals.push_back(cross.scale(cross.modulus()));
				}
			}
			sides.push_back(sidesTemp);
		}
	}
	virtual void draw();
	virtual void rotate(float ax, float ay);
};
#endif