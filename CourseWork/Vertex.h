#include <GL/glut.h>
#ifndef __VERTEX_H__
#define __VERTEX_H__
class Vertex {
private:
	float x, y, z, r, g, b;
public:
	Vertex(float x, float y, float z, float r = 1.0, float g = 1.0, float b = 1.0) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->r = r;
		this->g = g;
		this->b = b;
	}
	virtual void drawGlVertex();
	virtual Vertex getProjectedVertex();
	virtual Vertex rotate(float yaw, float pitch, float roll);
};
#endif
