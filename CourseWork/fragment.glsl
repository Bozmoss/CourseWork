//fragment shader

#version 440 core

out vec4 FragColor;
uniform vec3 i_res;

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
    vec3 c1 = vec3(0.5, 0.0, 0.0);
    float r1 = 1.0;
    vec3 c2 = vec3(-0.5f, 0.0, 0.0);
    float r2 = 1.0;
    return intersectSDF(sphereSDF(p, c1, r1), sphereSDF(p, c2, r2));;
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
    return t; //TODO: Phong reflection model
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
    if (rayMarch(ro, rd, maxDist) < maxDist) {
        col = vec3(1.0, 0.0, 0.0);
    }

    FragColor = vec4(col, 1.0);
}