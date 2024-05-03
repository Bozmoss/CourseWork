#include <GL/glut.h>
#ifndef __VERTEX_H__
#define __VERTEX_H__
class Vertex {
private:
	float x, y, z;
public:
	Vertex(float x = 0, float y = 0, float z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	virtual void drawGlVertex();
	virtual Vertex getProjectedVertex();
	virtual Vertex rotateAboutX(float a);
	virtual Vertex rotateAboutY(float a);
};
#endif
