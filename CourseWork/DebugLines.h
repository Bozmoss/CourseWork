#include <GL/glut.h>
#include "Vertex.h"
#ifndef __DEBUGLINES_H__
#define __DEBUGLINES_H__
class DebugLines {
private:
	Vertex origin = Vertex(0, 0, 0);
	Vertex x = Vertex(2, 0, 0);
	Vertex y = Vertex(0, 2, 0);
	Vertex z = Vertex(0, 0, 2);
public:
	virtual void draw(float ax, float ay);
};
#endif