#include <GL/glut.h>
#include <cmath>
#include "PVector.h"
#include "GLOBAL.h"

void PVector::drawGlPVector() {
	glColor3f(r, g, b);
	glVertex3f(x, y, z);
}

PVector PVector::getProjectedPVector() {
	return PVector(FOV * (x) / (FOV + z), FOV * (y) / (FOV + z), 0, r, g, b);
}

PVector PVector::rotate(float ax, float ay) {
	return PVector(x * cos(ay) + z * sin(ay), x * sin(ax) * sin(ay) - z * sin(ax) * cos(ay) + y * cos(ax), -x * cos(ax) * sin(ay) + z * cos(ax) * cos(ay) + y * sin(ax), r, g, b);
}

PVector PVector::crossProd(PVector v) {
    return PVector(y * v.getZ() - z * v.getY(), z * v.getX() - x * v.getZ(), x * v.getY() - y * v.getX());
}

double PVector::dotProd(PVector v) {
    return x * v.getX() + y * v.getY() + z * v.getZ();
}

PVector PVector::transform(PVector v) {
    return PVector(x + v.getX(), y + v.getY(), z + v.getZ());
}

void PVector::scale(float m) {
    x *= m, y *= m, z *= m;
}

double PVector::getMagnitude() {
    return sqrt(x * x + y * y + z * z);
}

void PVector::setRGB(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

float PVector::getX() {
    return x;
}

float PVector::getY() {
    return y;
}

float PVector::getZ() {
    return z;
}

void PVector::setX(float newX) {
    x = newX;
}

void PVector::setY(float newY) {
    y = newY;
}

void PVector::setZ(float newZ) {
    z = newZ;
}