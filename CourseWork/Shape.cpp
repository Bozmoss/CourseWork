#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <vector>
#include <math.h>
#include <iostream>
#include "Shape.h"
#include "GLOBAL.h"

void Shape::draw(float ax, float ay) {
    transform = transform.rotate(ax, ay);
    rotate(ax, ay);
    updateNormals();
    calculateSideClearance();
    for (int i = 0; i < sides.size(); i++) {
        if (camVecAngles.at(i) > 0) {
            glBegin(GL_POLYGON);
            for (int j = 0; j < sides.at(i).size(); j++) {
                sides.at(i).at(j).getProjectedPVector().drawGlPVector();
            }
            glEnd();
            glBegin(GL_LINE_LOOP);
            for (int j = 0; j < sides.at(i).size(); j++) {
                PVector current = sides.at(i).at(j).getProjectedPVector();
                current.setRGB(0, 0, 0);
                current.drawGlPVector();
            }
            glEnd();
        }
    }
    glBegin(GL_POINTS);
    for (int i = 0; i < normals.size(); i++) {
        PVector current = normals.at(i).getProjectedPVector();
        current.setRGB(0, 1, 1);
        current.drawGlPVector();
    }
    glEnd();
}

void Shape::rotate(float ax, float ay) {
    std::vector<std::vector<PVector>>* sidesTemp = new std::vector<std::vector<PVector>>;
    for (int i = 0; i < sides.size(); i++) {
        std::vector<PVector>* side = new std::vector<PVector>;
        for (int j = 0; j < sides.at(i).size(); j++) {
            side->push_back(sides.at(i).at(j).rotate(ax, ay));
        }
        sidesTemp->push_back(*side);
        delete side;
        side = nullptr;
    }
    sides.swap(*sidesTemp);
    delete sidesTemp;
    sidesTemp = nullptr;
}

void Shape::updateNormals() {
    std::vector<PVector>* normalsTemp = new std::vector<PVector>;
    for (int i = 0; i < sides.size(); i++) {
        for (int j = 0; j < sides.at(i).size(); j++) {
            if (j == 0) {
                PVector v1 = PVector(sides.at(i).at(j+1).getX() - sides.at(i).at(j).getX(), sides.at(i).at(j+1).getY() - sides.at(i).at(j).getY(), sides.at(i).at(j+1).getZ() - sides.at(i).at(j).getZ());
                PVector v2 = PVector(sides.at(i).at(j+2).getX() - sides.at(i).at(j).getX(), sides.at(i).at(j+2).getY() - sides.at(i).at(j).getY(), sides.at(i).at(j+2).getZ() - sides.at(i).at(j).getZ());
                PVector cross = v1.crossProd(v2);
                cross.scale(1 / cross.getMagnitude());
                normalsTemp->push_back(cross.transform(transform));
            }
        }
    }
    normals.swap(*normalsTemp);
    delete normalsTemp;
    normalsTemp = nullptr;
}

void Shape::calculateSideClearance() {
    camVecAngles.clear();
    PVector v(0, 0, 1-DEPTH);
    for (int i = 0; i < normals.size(); i++) {
        PVector camVec(normals.at(i).getX(), normals.at(i).getY(), normals.at(i).getZ());
        //if (i == 0) {
            glBegin(GL_LINE_LOOP);
            v.getProjectedPVector().drawGlPVector();
            normals.at(i).getProjectedPVector().drawGlPVector();
            glEnd();
        //}
        camVecAngles.push_back(acos(camVec.dotProd(v)/(camVec.getMagnitude() * v.getMagnitude())) * 180/M_PI - 90);
        //camVecAngles.push_back(camVec.getMagnitude());
        if (i % 2 == 0) {
            std::cout << camVecAngles.at(i) << " ";
        }
    }
    std::cout << std::endl;
}