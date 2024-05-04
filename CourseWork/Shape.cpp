#include <GL/glut.h>
#include <iterator>
#include <list>
#include "Shape.h"

void Shape::draw() {
	glBegin(GL_POINTS);
	for (it = vertices.begin(); it != vertices.end(); it++) {
		(*it).getProjectedVertex().drawGlVertex();
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