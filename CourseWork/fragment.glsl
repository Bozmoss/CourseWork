//fragment shader

#version 440 core

out vec4 FragColor;
uniform vec3 i_res;
uniform vec3 lightPos;

float sphereSDF(vec3 p, vec3 c, float r) {
    return length(c-p) - r;
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

float finalSDF(vec3 p) {
    vec3 c1 = vec3(0.0, 0.0, 0.0);
    float r1 = 1.0;
    return sphereSDF(p, c1, r1);
}

float rayMarch(vec3 ro, vec3 rd, float maxDist) {
    float t = 0.0;
    for (int i = 0; i < 100; i++) {
        vec3 pos = ro + t * rd;
        float dist = finalSDF(pos);
        if (dist < 0.001) break;
        t += dist;
        if (t > maxDist) break;
    }
    return t;
}

vec3 calculateNormal(vec3 p, vec3 c, float r) {
    const float eps = 0.0001;
    const vec2 epsVec = vec2(eps, 0);
    return normalize(vec3(
        sphereSDF(p+epsVec.xyy, c, r) - sphereSDF(p-epsVec.xyy, c, r),
        sphereSDF(p+epsVec.yxy, c, r) - sphereSDF(p-epsVec.yxy, c, r),
        sphereSDF(p+epsVec.yyx, c, r) - sphereSDF(p-epsVec.yyx, c, r)
    ));
}
//Ia = intensity of scene (UI), Ka = intensity of material (UI) [Ambiant component]
//Kd = diffuse intensity (UI), Ii = diffuse intensity of ith light (UI), n = normal vector at p, li = lightPos  - p [Diffuse component]
//c = coefficent of specular reflection (UI), v = cameraPos - p, Ks = specular intensity (UI)
float getCol(float Ia, float Ka, float Kd, float Ii, vec3 n, vec3 li, float c, vec3 v, float Ks) {
    return Ia * Ka + dot(n, normalize(li)) * Kd * Ii; //investigate specular component
}

void main()
{
    vec2 uv = gl_FragCoord.xy / i_res.xy;
    uv = uv * 2.0 - 1.0;
    uv.x *= i_res.x / i_res.y;

    vec3 ro = vec3(0.0, 0.0, 2.0);
    vec3 rd = normalize(vec3(uv, -1.0));
    float maxDist = 10.0;

    vec3 col = vec3(0.0);
    float t = rayMarch(ro, rd, maxDist);
    if (t < maxDist) {
        col = vec3(0.01, 0.0, 0.0) * getCol(10.0, 10.0, 1.0, 1.0, calculateNormal(ro + t * rd, vec3(0.0, 0.0, 0.0), 1.0), lightPos - (ro + t * rd), 1.0, vec3(1.0), 1.0);
    }

    FragColor = vec4(col, 1.0);
}