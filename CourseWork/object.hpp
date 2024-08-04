#pragma once

struct Object {
    int type, material;
    float x, y, z, l1, dx, dy, dz;
    bool down = true, moving = false;
};