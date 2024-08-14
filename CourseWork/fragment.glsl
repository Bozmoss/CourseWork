//fragment shader

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

struct SDF {
    float dist;
    int index;
};

SDF sphereSDF(vec3 p, vec3 c, float r, int i) { //0
    return SDF(length(c-p) - r, i);
}

SDF torusSDF(vec3 p, vec2 t, int i) { //1
    vec2 q = vec2(length(p.xz)-t.x,p.y);
    return SDF(length(q)-t.y, i);
}

SDF planeSDF(vec3 p, vec3 n, float h, int i) { //2
  return SDF(dot(p, n) + h, i);
}

SDF unionSDF(SDF SDF1, SDF SDF2) {
    return (SDF1.dist < SDF2.dist) ? SDF1 : SDF2;
}

SDF intersectSDF(SDF SDF1, SDF SDF2) {
    return (SDF1.dist > SDF2.dist) ? SDF1 : SDF2;
}

SDF subSDF(SDF SDF1, SDF SDF2) {
    if (SDF1.dist > -SDF2.dist) {
        return SDF1;
    }
    return SDF2;
}

mat3 rotateX(float a) {
    float s = sin(a), c = cos(a);
    return mat3(
    1.0, 0.0, 0.0,
    0.0, c, -s,
    0.0, s, c);
}

mat3 rotateY(float a) {
    float s = sin(a), c = cos(a);
    return mat3(
    c, 0.0, s,
    0.0, 1.0, 0.0,
    -s, 0.0, c);
}

vec3 rotateSDF(vec3 p, float x, float y) {
    mat3 rotX = rotateX(x);
    mat3 rotY = rotateY(y);
    return p * rotY * rotX;
}

vec3 translateSDF(vec3 p, vec3 t) {
    return p - t;
}

SDF finalSDF(vec3 p) {
    SDF final = planeSDF(p, vec3(0.0, 1.0, 0.0), 1.5, 2);
    for (int i = 0; i < objectsL; i++) {
        SDF temp;
        switch(int(objects[i].type)) {
            case 0:
                temp = sphereSDF(p, vec3(objects[i].x, objects[i].y, objects[i].z), objects[i].l1, int(objects[i].material));
                break;
            case 1:
                temp = torusSDF(p, vec2(objects[i].x, objects[i].y), int(objects[i].material));
                break;
            case 2:
                temp = planeSDF(p, vec3(objects[i].x, objects[i].y, objects[i].z), objects[i].l1, int(objects[i].material));
                break;
        };
        final = unionSDF(final, temp);
    }
    return final;
}

vec3 calculateNormal(vec3 p) {
    const float eps = 0.0001;
    const vec2 epsVec = vec2(eps, 0);
    return normalize(vec3(
        finalSDF(p+epsVec.xyy).dist - finalSDF(p-epsVec.xyy).dist,
        finalSDF(p+epsVec.yxy).dist - finalSDF(p-epsVec.yxy).dist,
        finalSDF(p+epsVec.yyx).dist - finalSDF(p-epsVec.yyx).dist
    ));
}

bool isInShadow(vec3 p, vec3 rd, float dist) {
    float t = 0.01;
    for (int i = 0; i < 100; i++) {
        vec3 pos = p + t * rd;
        SDF res = finalSDF(pos);
        if (res.dist < 0.001) {
            return true;
        }
        t += res.dist;
        if (t >= dist) {
            return false;
        }
    }
    return false;
}

vec3 getCol(vec3 Ia, Material m, vec3 Ii[lightsLen], vec3 n, vec3 li[lightsLen], vec3 v, vec3 p) {
    vec3 a = Ia * m.Ka;
    vec3 d = vec3(0.0);
    vec3 s = vec3(0.0);
    for (int i = 0; i < lightsL; i++) {
        vec3 light = normalize(li[i] - p);
        float dist = length(light);
        if (!isInShadow(p, light, dist)) {
            vec3 r = reflect(-light, n);
            d += max(dot(n, light), 0.0) * m.Kd * Ii[i] * vec3(m.r, m.g, m.b);
            s += m.Ks * pow(max(dot(r, normalize(v)), 0.0), m.c) * Ii[i];
        }
    }
    return a + d + s;
}

vec2 rayMarch(vec3 ro, vec3 rd, float maxDist) {
    float t = 0.0;
    vec3 pos;
    int ind = -1;
    for (int i = 0; i < 100; i++) {
        pos = ro + t * rd;
        SDF res = finalSDF(pos);
        if (res.dist < 0.001) {
            ind = res.index;
            break;
        }
        t += res.dist;
        if (t > maxDist) break;
    }
    return vec2(t, ind);
}

vec3 checkerFloor(vec3 p) {
    float scale = 1.0;
    int checker = int(floor(p.x * scale) + floor(p.z * scale)) % 2;
    return (checker == 0) ? vec3(1.0) : vec3(0.0);
}

vec3 sortCol(vec3 ro, vec3 rd, float maxDist) {
    vec3 c = vec3(0.0, 0.0, 0.0);
    float Rf = 1.0;

    for (int depth = 0; depth < 3; depth++) {
        vec2 t = rayMarch(ro, rd, maxDist);
        vec3 pos = ro + t.x * rd;
        if (t.x < maxDist && t.y >= 0) {
            vec3 n = calculateNormal(pos);
            vec3 view = normalize(ro - pos);
            vec3 Ia = vec3(1.0);
            vec3 surfaceC = getCol(Ia, materials[int(t.y)], lightCols, n, lights, view, pos);

            if (int(t.y) == 2) {
                surfaceC = checkerFloor(pos);
                float Ff = clamp(1.0 - (length(pos - ro) / maxDist), 0.0, 1.0);
                surfaceC = mix(c, surfaceC, Ff);
            }

            c += Rf * surfaceC;
            Rf *= materials[int(t.y)].Kr;

            rd = reflect(rd, n);
            ro = pos + n * 0.01;
        } else {
            break;
        }
    }
    return c;
}

void main()
{
    vec2 uv = gl_FragCoord.xy / res.xy;
    uv = uv * 2.0 - 1.0;
    uv.x *= res.x / res.y;

    vec3 ro = vec3(0.0, 0.0, 2.0);
    vec3 rd = normalize(vec3(uv, -1.0));
    mat3 rotX = rotateX(aX);
    mat3 rotY = rotateY(aY);
    ro = ro * rotX * rotY;
    rd = rd * rotX * rotY;

    float maxDist = 10.0;

    vec3 col = sortCol(ro, rd, maxDist);

    FragColor = vec4(col, 1.0);
}