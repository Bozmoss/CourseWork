#include <GL/glut.h>
#include <iterator>
#include <list>
#include "Shape.h"

void Shape::draw() {
	glBegin(GL_POINTS);
	list<Vertex>::iterator it;
	for (it = vertices.begin(); it != vertices.end(); it++) {
		(*it).getProjectedVertex().drawGlVertex();
	}
	glEnd();
}