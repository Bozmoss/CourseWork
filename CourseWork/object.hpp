#pragma once

#include <vector>

struct ObjectData {
    int type, material;
    float x, y, z, l1, dx, dy, dz;
    bool down = true, moving = false;
};

class Object {
protected:
    ObjectData data;
    float lastT;
    float SDF() {}
public:
    Object(ObjectData data);

    void update(float f);

    void applyGravity(float g, float r);

    void stopMoving();

    bool isClicked(float xpos, float ypos, float zpos, float finalT) { return false; }

    float getLastT();

    ObjectData *getData();
};

class Sphere : public Object {
protected:
    float SDF(float px, float py, float pz, float cx, float cy, float cz, float r);
public:
    Sphere(ObjectData data) : Object(data) {}
    bool isClicked(float xpos, float ypos, float zpos, float finalT);
};