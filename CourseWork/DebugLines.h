#pragma once
#include <GL/glut.h>
#include "PVector.h"
class DebugLines {
private:
	PVector origin = PVector(0, 0, 0);
	PVector x = PVector(2, 0, 0);
	PVector y = PVector(0, 2, 0);
	PVector z = PVector(0, 0, 2);
public:
	virtual void draw(float ax, float ay);
};