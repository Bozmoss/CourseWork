#include <GL/glut.h>
#include "DebugLines.h"

void DebugLines::draw(float ax, float ay) {
	glBegin(GL_LINE_STRIP);
	origin.setRGB(1, 0, 0);
	x.setRGB(1, 0, 0);
	origin.rotate(ax, ay).getProjectedVertex().drawGlVertex();
	x.rotate(ax, ay).getProjectedVertex().drawGlVertex();
	glEnd();
	glBegin(GL_LINE_STRIP);
	origin.setRGB(0, 1, 0);
	y.setRGB(0, 1, 0);
	origin.rotate(ax, ay).getProjectedVertex().drawGlVertex();
	y.rotate(ax, ay).getProjectedVertex().drawGlVertex();
	glEnd();
	glBegin(GL_LINE_STRIP);
	origin.setRGB(0, 0, 1);
	z.setRGB(0, 0, 1);
	origin.rotate(ax, ay).getProjectedVertex().drawGlVertex();
	z.rotate(ax, ay).getProjectedVertex().drawGlVertex();
	glEnd();
}