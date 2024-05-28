#include <GL/glut.h>
#include <cmath>
#include "PVector.h"
#include "GLOBAL.h"
#include "AffineMatrix.h"

void PVector::drawGlPVector() {
	glColor3f(r, g, b);
	glVertex3f(x, y, z);
}

PVector PVector::getProjectedPVector() {
	return PVector(FOV * (x) / (FOV + z), FOV * (y) / (FOV + z), 0, r, g, b);
}

PVector PVector::rotate(float ax, float ay) {
    AffineMatrix X(ax, 'x');
    AffineMatrix Y(ay, 'y');
    AffineMatrix rotation = X.multiply(Y);
    return matrixTransform(rotation);
}

PVector PVector::rotate(float ax, float ay, PVector &_CAM) {
    AffineMatrix X(ax, 'x');
    AffineMatrix Y(ay, 'y');
    AffineMatrix rotation = X.multiply(Y);
    _CAM = _CAM.matrixTransform(rotation.inverse());
    return matrixTransform(rotation);
}

PVector PVector::rotate(float ax, float ay) {
    AffineMatrix X(ax, 'x');
    AffineMatrix Y(ay, 'y');
    AffineMatrix rotation = X.multiply(Y);
    return matrixTransform(rotation);
}

PVector PVector::crossProd(PVector v) {
    return PVector(y * v.getZ() - z * v.getY(), z * v.getX() - x * v.getZ(), x * v.getY() - y * v.getX());
}

double PVector::dotProd(PVector v) {
    return x * v.getX() + y * v.getY() + z * v.getZ();
}

PVector PVector::transform(PVector v, PVector &transformInv) {
    AffineMatrix T(v.getX(), v.getY(), v.getZ());
    transformInv = matrixTransform(T.inverse());
    return matrixTransform(T);
}

PVector PVector::transform(PVector v) {
    AffineMatrix T(v.getX(), v.getY(), v.getZ());
    return matrixTransform(T);
}

PVector PVector::matrixTransform(AffineMatrix m) {
    return PVector(m.atPos(0, 0) * x + m.atPos(0, 1) * y + m.atPos(0, 2) * z + m.atPos(0, 3),
        m.atPos(1, 0) * x + m.atPos(1, 1) * y + m.atPos(1, 2) * z + m.atPos(1, 3),
        m.atPos(2, 0) * x + m.atPos(2, 1) * y + m.atPos(2, 2) * z + m.atPos(2, 3));
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