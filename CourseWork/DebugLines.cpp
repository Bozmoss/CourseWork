#include <GL/glut.h>
#include "DebugLines.h"

void DebugLines::draw(float ax, float ay) {
	glBegin(GL_LINE_STRIP);
	origin.setRGB(1, 0, 0);
	x.setRGB(1, 0, 0);
	origin.rotate(ax, ay).getProjectedPVector().drawGlPVector();
	x.rotate(ax, ay).getProjectedPVector().drawGlPVector();
	glEnd();
	glBegin(GL_LINE_STRIP);
	origin.setRGB(0, 0, 1);
	z.setRGB(0, 0, 1);
	origin.rotate(ax, ay).getProjectedPVector().drawGlPVector();
	z.rotate(ax, ay).getProjectedPVector().drawGlPVector();
	glEnd();
	glBegin(GL_LINE_STRIP);
	origin.setRGB(0, 1, 0);
	y.setRGB(0, 1, 0);
	origin.rotate(ax, ay).getProjectedPVector().drawGlPVector();
	y.rotate(ax, ay).getProjectedPVector().drawGlPVector();
	glEnd();
}