#include "object.hpp"

#include <iostream>

Object::Object(ObjectData data):
    data{ data }, 
    lastT{ 0 } {}

float Object::SDF() {}

void Object::update(float f) {
    if (data.y - data.l1 <= -1.5 && !data.moving) {
        data.dx *= f;
    }
    data.x += data.dx;
    data.y += data.dy;
    data.z += data.dz;
}

void Object::applyGravity(float g, float r) {
    if (!data.moving) {
        if (data.down) {
            data.dy -= g;
            if (data.y - data.l1 < -1.5) {
                data.y = -1.5 + data.l1;
                data.dy = -data.dy * r;
                if (abs(data.dy) < 0.000001) {
                    data.dy = 0.0;
                    data.down = false;
                }
            }
        }
        else {
            data.dy -= g;
            if (data.dy <= 0) {
                data.down = true;
            }
        }
    }
}

void Object::stopMoving() {
    data.moving = false;
}

bool Object::isClicked(std::vector<float> ro, std::vector<float> rd, float finalT) {
    return false;
}

float Object::getLastT() {
    return lastT;
}

void Object::reset() {
    lastT = 0;
}

ObjectData *Object::getData() {
    return &data;
}


float Sphere::SDF(float px, float py, float pz, float cx, float cy, float cz, float r) {
    return sqrt(
        (cx - px) * (cx - px) +
        (cy - py) * (cy - py) +
        (cz - pz) * (cz - pz)
    ) - r;
}

bool Sphere::isClicked(std::vector<float> ro, std::vector<float> rd, float finalT) {
    float t = 0.0f;
    for (int i = 0; i < 100; i++) {
        std::vector<float> p = {
            ro.at(0) + t * rd.at(0),
            ro.at(1) + t * rd.at(1),
            ro.at(2) + t * rd.at(2)
        };
        float sdf = SDF(p.at(0), p.at(1), p.at(2), data.x, data.y, data.z, data.l1);
        //std::cout << "SDF at t = " << t << ": " << sdf << "\n";
        if (sdf < 0.001f && t < finalT) {
            lastT = t;
            return true;
        }
        t += sdf;
        if (t > 100.0f) {
            lastT = t;
            break;
        }
    }
    return false;
}