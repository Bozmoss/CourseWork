#include <GL/glut.h>
#include <cmath>
#include "Vertex.h"
#include "GLOBAL.h"

void Vertex::drawGlVertex() {
	glColor3f(r, g, b);
	glVertex3f(x, y, z);
}

Vertex Vertex::getProjectedVertex() {
	return Vertex(FOV * (x) / (FOV + z), FOV * (y) / (FOV + z), 0, r, g, b);
}

Vertex Vertex::rotate(float ax, float ay) {
	return Vertex(x * cos(ay) + z * sin(ay), x * sin(ax) * sin(ay) - z * sin(ax) * cos(ay) + y * cos(ax), -x * cos(ax) * sin(ay) + z * cos(ax) * cos(ay) + y * sin(ax), r, g, b);
}

void Vertex::setRGB(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

float Vertex::getX() {
    return x;
}

float Vertex::getY() {
    return y;
}

float Vertex::getZ() {
    return z;
}
