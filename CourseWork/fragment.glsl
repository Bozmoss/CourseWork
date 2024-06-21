//fragment shader

#version 440 core

out vec4 FragColor;
uniform vec3 i_res;
uniform float aY, aX;
vec3 lights[3];
vec3 lightCols[3];

struct Material {
    vec3 color;
    float Ka; //Coefficient of ambience
    float Kd; //Coefficient of diffuse
    float Ks; //Coefficenet of speculance
    float c; //Shininess
};

Material materials[2];

void setup() {
    materials[0] = Material(vec3(1.0, 0.0, 0.0), 0.2, 0.7, 0.5, 32.0);
    materials[1] = Material(vec3(0.0, 1.0, 0.0), 0.2, 0.7, 0.5, 32.0);
    lights[0] = vec3(2.0, 0.6, 1.0);
    lights[1] = vec3(-2.0, 0.6, 1.0);
    lights[2] = vec3(0.0, 0.8, 1.0);
    lightCols[0] = vec3(1.0);
    lightCols[1] = vec3(1.0);
    lightCols[2] = vec3(1.0);
}

struct SDF {
    float dist;
    int index;
};

SDF sphereSDF(vec3 p, vec3 c, float r, int i) {
    return SDF(length(c-p) - r, i);
}

SDF torusSDF(vec3 p, vec2 t, int i) {
    vec2 q = vec2(length(p.xz)-t.x,p.y);
    return SDF(length(q)-t.y, i);
}

SDF planeSDF(vec3 p, vec4 n, int i) {
  return SDF(dot(p,n.xyz) + n.w, i);
}

SDF unionSDF(SDF SDF1, SDF SDF2) {
    return (SDF1.dist < SDF2.dist) ? SDF1 : SDF2;
}

SDF intersectSDF(SDF SDF1, SDF SDF2) {
    if (SDF1.dist > SDF2.dist) {
        return SDF1;
    }
    return SDF2;
}

SDF subSDF(SDF SDF1, SDF SDF2) {
    if (SDF1.dist > -SDF2.dist) {
        return SDF1;
    }
    return SDF2;
}

vec3 rotateSDF(vec3 p, float x, float y) {
    mat3 rot = mat3(
        cos(y), 0, sin(y),
        sin(x) * sin(y), cos(x), -cos(y) * sin(x),
        -cos(x) * sin(y), sin(x), cos(x) * cos(y)
    );
    p *= inverse(rot);
    return p;
}

SDF finalSDF(vec3 p) {
    SDF s1 = sphereSDF(rotateSDF(p, aX, aY), vec3(0.0), 0.5, 0);
    SDF s2 = sphereSDF(rotateSDF(p, aX, aY), vec3(0.8, 0.0, 0.0), 0.2, 1);
    return unionSDF(s1, s2);
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

//Ia = intensity of scene (UI), Ka = intensity of material (UI) [Ambiant component]
//Kd = diffuse intensity (UI), Ii = diffuse intensity of ith light (UI), n = normal vector at p, li = lightPos  - p [Diffuse component]
//c = coefficent of specular reflection (UI), v = cameraPos - p, Ks = specular intensity (UI)
vec3 getCol(vec3 Ia, Material m, vec3 Ii[3], vec3 n, vec3 li[3], vec3 v, vec3 p) {
    vec3 a = Ia * m.Ka;
    vec3 d = vec3(0.0);
    vec3 s = vec3(0.0);
    for (int i = 0; i < 3; i++) {
        vec3 light = normalize(li[i] - p);
        vec3 r = reflect(-light, n);
        d += max(dot(n, light), 0.0) * m.Kd * Ii[i] * m.color;
        s += m.Ks * pow(max(dot(r, normalize(v)), 0.0), m.c) * Ii[i];
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

vec3 sortCol(vec3 ro, vec3 rd, float maxDist) {
    vec2 t = rayMarch(ro, rd, maxDist);
    vec3 pos = ro + t.x * rd;
    if (t.x < maxDist && t.y >= 0) {
        vec3 n = calculateNormal(pos);
        vec3 view = normalize(ro - pos);
        vec3 Ia = vec3(1.0);
        vec3 Ii = vec3(1.0);
        vec3 c1 = getCol(Ia, materials[int(t.y)], lightCols, n, lights, view, pos);
        return c1;
    }
    return vec3(0.0, 0.0, 1.0);
}

void main()
{
    setup();
    vec2 uv = gl_FragCoord.xy / i_res.xy;
    uv = uv * 2.0 - 1.0;
    uv.x *= i_res.x / i_res.y;

    vec3 ro = vec3(0.0, 0.0, 2.0);
    vec3 rd = normalize(vec3(uv, -1.0));
    float maxDist = 10.0;

    vec3 col = sortCol(ro, rd, maxDist);

    FragColor = vec4(col, 1.0);
}