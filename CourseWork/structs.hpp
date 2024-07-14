#pragma once

struct Material {
    float r, g, b, Ka, Kd, Ks, Kr, c;
};

struct Object {
    int type, material;
    float x, y, z, l1;
};

struct ubData {
    Material m;
    Object o;
};