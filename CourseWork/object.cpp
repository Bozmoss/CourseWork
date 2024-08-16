#include "object.hpp"

Object::Object(ObjectData data):
    data{ data }, 
    lastT{ 0 } {}

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

float Object::getLastT() {
    return lastT;
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

bool Sphere::isClicked(float xpos, float ypos, float zpos, float finalT) {
    float t = 0.0;
    const float maxT = 10.0;
    while (t < maxT) {
        float p[3] = {
            t * xpos,
            t * ypos,
            t * zpos
        };
        float res = SDF(
            p[0],
            p[1],
            p[2],
            data.x,
            data.y,
            data.z,
            data.l1
        );
        if (res < 0.0001) {
            break;
        }
        t += res;
    }
    lastT = t;
    return (t < finalT && t < maxT);
}