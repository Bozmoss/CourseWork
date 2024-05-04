#include <GL/glut.h>
#include <cmath>
#include "Vertex.h"
#include "GLOBAL.h"

void Vertex::drawGlVertex() {
	glColor3f(r, g, b);
	glVertex3f(x, y, z);
}

Vertex Vertex::getProjectedVertex() {
	return Vertex(FOV * (x) / (FOV + z), FOV * (y) / (FOV + z), 0);
}

Vertex Vertex::rotate(float ax, float ay) {
	return Vertex(x * cos(ay) + z * sin(ay), x * sin(ax) * sin(ay) - z * sin(ax) * cos(ay) + y * cos(ax), -x * cos(ax) * sin(ay) + z * cos(ax) * cos(ay) + y * sin(ax));
}
