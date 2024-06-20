//fragment shader

#version 440 core

out vec4 FragColor;
uniform vec3 i_res;
uniform float aY, aX;
vec3 lightPos = vec3(1.0, 1.0, 0.5);

float sphereSDF(vec3 p, vec3 c, float r) {
    return length(c-p) - r;
}

float torusSDF(vec3 p, vec2 t) {
    vec2 q = vec2(length(p.xz)-t.x,p.y);
    return length(q)-t.y;
}

float planeSDF(vec3 p, vec4 n) {
  return dot(p,n.xyz) + n.w;
} 

float unionSDF(float SDF1, float SDF2) {
    return min(SDF1, SDF2);
}

float intersectSDF(float SDF1, float SDF2) {
    return max(SDF1, SDF2);
}

float subSDF(float SDF1, float SDF2) {
    return max(SDF1, -SDF2);
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

float finalSDF(vec3 p) {
    //float s1 = sphereSDF(rotateSDF(p, aX, aY), vec3(0.0), 0.5);
    //float s2 = sphereSDF(rotateSDF(p, aX, aY), vec3(1.0, 0.0, 0.0), 0.2);
    float p1 = planeSDF(rotateSDF(p, aX, aY), vec4(0.0, 0.0, 1.0, 1.0));
    float p2 = planeSDF(rotateSDF(p, aX, aY), vec4(1.0, 0.0, 0.0, -1.0));
    return unionSDF(p1, p2);
}

vec3 calculateNormal(vec3 p) {
    const float eps = 0.0001;
    const vec2 epsVec = vec2(eps, 0);
    return normalize(vec3(
        finalSDF(p+epsVec.xyy) - finalSDF(p-epsVec.xyy),
        finalSDF(p+epsVec.yxy) - finalSDF(p-epsVec.yxy),
        finalSDF(p+epsVec.yyx) - finalSDF(p-epsVec.yyx)
    ));
}

//Ia = intensity of scene (UI), Ka = intensity of material (UI) [Ambiant component]
//Kd = diffuse intensity (UI), Ii = diffuse intensity of ith light (UI), n = normal vector at p, li = lightPos  - p [Diffuse component]
//c = coefficent of specular reflection (UI), v = cameraPos - p, Ks = specular intensity (UI)
vec3 getCol(vec3 Ia, float Ka, float Kd, vec3 Ii, vec3 n, vec3 li, float c, vec3 v, float Ks) {
    vec3 a = Ia * Ka;
    vec3 d = max(dot(n, normalize(li)), 0.0) * Kd * Ii;
    vec3 r = reflect(-normalize(li), n);
    float spec = pow(max(dot(r, normalize(v)), 0.0), c);
    vec3 s = Ks * spec * Ii;
    return a + d + s;
}

vec3 rayMarch(vec3 ro, vec3 rd, float maxDist) {
    float t = 0.0;
    vec3 pos;
    for (int i = 0; i < 100; i++) {
        pos = ro + t * rd;
        float dist = finalSDF(pos);
        if (dist < 0.001) break;
        t += dist;
        if (t > maxDist) break;
    }
    if (t < maxDist) {
        vec3 n = calculateNormal(pos);
        vec3 light = normalize(lightPos - pos);
        vec3 view = normalize(ro - pos);
        vec3 col = getCol(vec3(1.0, 0.0, 0.0), 0.3, 0.7, vec3(1.0, 0.0, 0.0), n, light, 32.0, view, 0.5);
        return col;
    }
    return vec3(0.0);
}

void main()
{
    vec2 uv = gl_FragCoord.xy / i_res.xy;
    uv = uv * 2.0 - 1.0;
    uv.x *= i_res.x / i_res.y;

    vec3 ro = vec3(0.0, 0.0, 2.0);
    vec3 rd = normalize(vec3(uv, -1.0));
    float maxDist = 10.0;

    vec3 col = rayMarch(ro, rd, maxDist);

    FragColor = vec4(col, 1.0);
}