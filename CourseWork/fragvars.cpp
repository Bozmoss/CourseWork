#include "fragvars.hpp"

FragVars::FragVars(std::vector<float> &res, float &aX, float &aY, std::vector<std::vector<float>> &lights, std::vector<std::vector<float>> &lightCols, std::vector<Material> &materials) {
    this->res = res;
    this->aX = aX;
    this->aY = aY;
    this->lights = lights;
    this->lightCols = lightCols;
    this->materials = materials;
}

void FragVars::init(Program &p) {
    ub.fill(materials, p);
    resLocation = glGetUniformLocation(p.handle(), "res");
    aYLocation = glGetUniformLocation(p.handle(), "aY");
    aXLocation = glGetUniformLocation(p.handle(), "aX");
    timeLocation = glGetUniformLocation(p.handle(), "time");
    lightsLocation = glGetUniformLocation(p.handle(), "lights");
    lightColsLocation = glGetUniformLocation(p.handle(), "lightCols");
    lightsLLocation = glGetUniformLocation(p.handle(), "lightsL");
    materialsLLocation = glGetUniformLocation(p.handle(), "materialsL");
    time = std::chrono::high_resolution_clock::now();
}
void FragVars::update(float &aX, float &aY) {
    this->aX = aX;
    this->aY = aY;
    glUniform3f(resLocation, res.at(0), res.at(1), res.at(2));
    glUniform1f(aXLocation, this->aX);
    glUniform1f(aYLocation, this->aY);
    glUniform1i(lightsLLocation, lights.size());
    glUniform1i(materialsLLocation, materials.size());
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = currentTime - time;
    glUniform1f(timeLocation, elapsed.count());
    GLfloat lightsArr[100][3], lightColsArr[100][3];
    for (int i = 0; i < 100; i++) {
        if (i < lights.size()) {
            for (int j = 0; j < 3; j++) {
                lightsArr[i][j] = lights.at(i).at(j);
            }
        }
        else {
            for (int j = 0; j < 3; j++) {
                lightsArr[i][j] = 0;
            }
        }
        if (i < lightCols.size()) {
            for (int j = 0; j < 3; j++) {
                lightColsArr[i][j] = lightCols.at(i).at(j);
            }
        }
        else {
            for (int j = 0; j < 3; j++) {
                lightColsArr[i][j] = 0;
            }
        }
    }
    glUniform3fv(lightsLocation, 100, &lightsArr[0][0]);
    glUniform3fv(lightColsLocation, 100, &lightColsArr[0][0]);
}