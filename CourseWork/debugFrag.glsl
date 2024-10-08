#version 440 core
#define lightsLen 100
#define materialsLen 100
#define objectsLen 100

out vec4 FragColor;
uniform vec3 res, lights[lightsLen], lightCols[lightsLen];
uniform float time, aX, aY;
uniform int lightsL, materialsL, objectsL;

struct Material {
    float r;
    float g;
    float b;
    float Ka;
    float Kd;
    float Ks;
    float Kr;
    float c;
};

struct ObjectData {
    float type;
    float material;
    float x;
    float y;
    float z;
    float l1;
};

layout(std140) uniform bindPoint {
    Material materials[materialsLen];
    ObjectData objects[objectsLen];
};

void main()
{
    vec3 debugColor = vec3(objects[0].type, objects[0].type, objects[1].l1);
    FragColor = vec4(debugColor, 1.0);
}