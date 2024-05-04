#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <iterator>
#include <list>
#include <cmath>
#include "Shape.h"

void Shape::draw() {
	glBegin(GL_QUADS);
	for (it = vertices.begin(); it != vertices.end(); it++) {
		Vertex current = (*it).getProjectedVertex();
		current.drawGlVertex();
		}
	glEnd();
}

void Shape::rotate(float ax, float ay) {
	list<Vertex> temp;
	for (it = vertices.begin(); it != vertices.end(); it++) {
		temp.push_back((*it).rotate(ax, ay));
	}
	vertices.clear();
	for (it = temp.begin(); it != temp.end(); it++) {
		vertices.push_back((*it));
	}
}