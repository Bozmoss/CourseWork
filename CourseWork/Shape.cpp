#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <iterator>
#include <list>
#include <cmath>
#include "Shape.h"

void Shape::draw() {
	for (it1 = sides.begin(); it1 != sides.end(); it1++) {
		glBegin(GL_LINE_LOOP);
		for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++) {
			(*it2).getProjectedVertex().drawGlVertex();
		}
		glEnd();
	}
}

void Shape::rotate(float ax, float ay) {
	list<list<Vertex>> temp;
	for (it1 = sides.begin(); it1 != sides.end(); it1++) {
		list<Vertex> temp1;
		for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++) {
			temp1.push_back((*it2).rotate(ax, ay));
		}
		temp.push_back(temp1);
	}
	sides.clear();
	for (it1 = temp.begin(); it1 != temp.end(); it1++) {
		list<Vertex> side;
		for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++) {
			side.push_back((*it2));
		}
		sides.push_back(side);
	}
}