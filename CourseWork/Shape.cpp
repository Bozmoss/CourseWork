#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <vector>
#include <iostream>
#include "Shape.h"

void Shape::draw() {
    //checkSides();
    //std::cout << sides.size() << std::endl;
    for (int i = 0; i < sides.size(); i++) {
        glBegin(GL_QUADS);
        for (int j = 0; j < sides.at(i).size(); j++) {
            sides.at(i).at(j).getProjectedVertex().drawGlVertex();
        }
        glEnd();
    }
}

void Shape::rotate(float ax, float ay) {
    std::vector<std::vector<Vertex>>* sidesTemp = new std::vector<std::vector<Vertex>>;
    for (int i = 0; i < sides.size(); i++) {
        std::vector<Vertex>* side = new std::vector<Vertex>;
        for (int j = 0; j < sides.at(i).size(); j++) {
            (*side).push_back(sides.at(i).at(j).rotate(ax, ay));
        }
        (*sidesTemp).push_back(*side);
        delete side;
        side = nullptr;
    }
    sides.swap(*sidesTemp);
    delete sidesTemp;
    sidesTemp = nullptr;
}

void Shape::checkSides() {
    
}