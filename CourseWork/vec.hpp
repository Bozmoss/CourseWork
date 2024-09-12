#pragma once

#include <cmath>

struct vec {
    float x, y, z;
};

class VecOps {
public:
    vec add(vec v1, vec v2);
    float dot(vec v1, vec v2);
    vec cross(vec v1, vec v2);
    vec scale(vec c, float s);
    float length(vec v);
    vec normalise(vec v);
};
