#include <GL/glut.h>
#include "Vector3.h"

Vector3 Vector3::crossProduct(Vector3 a) {
    float v[] = { a.j() * k() - a.k() * j(), a.k() * i() - a.i() * k(), a.i() * j() - a.j() * i() };
    float* vStart = &v[0];
    return Vector3(vStart);
}

float Vector3::modulus() {
    return vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2];
}

Vector3 Vector3::scale(float scalar) {
    float v[] = { vector[0] * scalar, vector[1] * scalar, vector[2] * scalar };
    float* vStart = &v[0];
    return Vector3(vStart);
}

float Vector3::i() {
    return vector[0];
}

float Vector3::j() {
    return vector[1];
}

float Vector3::k() {
    return vector[2];
}