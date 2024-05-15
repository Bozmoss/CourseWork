#include <GL/glut.h>
#include <list>
#include "Vertex.h"
#ifndef __SHAPE_H__
#define __SHAPE_H__
using namespace std;
class Shape {
private:
	list<list<Vertex>> sides;
    list<Vertex> sideCentres;
	list<list<Vertex>>::iterator it1;
	list<Vertex>::iterator it2;
public:
	Shape(Vertex* vArr, int len, int innerLen) {
		for (int i = 0, n = 0; i < len; i++) {
			list<Vertex> sidesTemp;
			for (int j = 0; j < innerLen; j++, n++) {
				sidesTemp.push_back(*(vArr + n));
			}
			sides.push_back(sidesTemp);
		}
	}
	virtual void draw();
	virtual void rotate(float ax, float ay);
};
#endif