#include <GL/glut.h>
#include <list>
#include "Vertex.h"
#ifndef __SHAPE_H__
#define __SHAPE_H__
using namespace std;
class Shape {
private:
	list<Vertex> vertices;
public:
	Shape(Vertex* vArr, int len) {
		for (int i = 0; i < len; i++) {
			vertices.push_back(*(vArr + i));
		}
	}
	virtual void draw();
};
#endif