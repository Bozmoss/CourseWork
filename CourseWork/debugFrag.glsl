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
    float Ka; //Coefficient of ambience
    float Kd; //Coefficient of diffuse
    float Ks; //Coefficenet of speculance
    float Kr; //Coefficenet of reflection
    float c; //Shininess
};

struct Object {
    float type;
    float material;
    float x;
    float y;
    float z;
    float l1;
};

layout(std140) uniform bindPoint {
    Material materials[materialsLen];
    Object objects[objectsLen];
};

void main()
{
    vec3 debugColor = vec3(objects[0].type, objects[0].type, objects[1].l1);

    // Temporary debug output to visualize the values
    FragColor = vec4(debugColor, 1.0);
}