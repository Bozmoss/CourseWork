#include <GL/glut.h>
#include <cmath>
#include "Vertex.h"
#include "GLOBAL.h"

void Vertex::drawGlVertex() {
	glVertex3f(x, y, z);
}

Vertex Vertex::getProjectedVertex() {
	return Vertex(FOV * (x) / (FOV + z), FOV * (y) / (FOV + z), 0);
}

Vertex Vertex::rotateAboutX(float a) {
	return Vertex();
}

Vertex Vertex::rotateAboutY(float a) {
	return Vertex();
}
