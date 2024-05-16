#pragma once
#include <GL/glut.h>
#include <list>
#include "Vertex.h"
using namespace std;
class Shape {
private:
	list<list<Vertex>> sides;
    list<Vertex> sideCentres;
	list<list<Vertex>>::iterator it1;
	list<Vertex>::iterator it2;
    virtual void checkSides();
    virtual list<list<Vertex>> sort2DList(list<list<Vertex>> l);
    virtual list<Vertex> sortList(list<Vertex> l, int mode);
public:
	Shape(Vertex* vArr, int len, int innerLen) {
		for (int i = 0, n = 0; i < len; i++) {
			list<Vertex> sidesTemp;
            float sumX = 0, sumY = 0, sumZ = 0;
			for (int j = 0; j < innerLen; j++, n++) {
                Vertex current = *(vArr + n);
                sidesTemp.push_back(current);
                sumX += current.getX();
                sumY += current.getY();
                sumZ += current.getZ();
			}
			sides.push_back(sidesTemp);
            sideCentres.push_back(Vertex(sumX / 3, sumY / 3, sumZ / 3, 0, 0, 0));
		}
	}
	virtual void draw();
	virtual void rotate(float ax, float ay);
};