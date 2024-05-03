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

Vertex Vertex::rotate(float yaw, float pitch, float roll) {
	return Vertex(
		x * cos(yaw) * cos(pitch) + y * (cos(yaw) * sin(pitch) * sin(roll) - sin(yaw) * cos(roll)) + z * (cos(yaw) * sin(pitch) * cos(roll) + sin(yaw) * sin(roll)),
		x * sin(yaw) * cos(pitch) + y * (sin(yaw) * sin(pitch) * sin(roll) + cos(yaw) * cos(roll)) + z * (sin(yaw) * sin(pitch) * cos(roll) - cos(yaw) * sin(roll)),
		-x * sin(pitch) + y * cos(pitch) * sin(roll) + z * cos(pitch) * cos(roll)
	);
}
