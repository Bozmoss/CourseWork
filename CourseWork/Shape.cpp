#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <vector>
#include <iostream>
#include "Shape.h"

void Shape::draw() {
    updateNormals();
    for (int i = 0; i < sides.size(); i++) {
        glBegin(GL_POLYGON);
        for (int j = 0; j < sides.at(i).size(); j++) {
            sides.at(i).at(j).getProjectedVertex().drawGlVertex();
        }
        glEnd();
        /*glBegin(GL_LINE_LOOP);
        for (int j = 0; j < sides.at(i).size(); j++) {
            Vertex current = sides.at(i).at(j).getProjectedVertex();
            current.setRGB(0, 0, 0);
            current.drawGlVertex();
        }
        glEnd();*/
    }
    glBegin(GL_POINTS);
    for (int i = 0; i < normals.size(); i++) {
        Vertex current = normals.at(i).getProjectedVertex();
        current.setRGB(0, 0, 0);
        current.drawGlVertex();
    }
    glEnd();
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

void Shape::updateNormals() {
    std::vector<Vertex>* normalsTemp = new std::vector<Vertex>;
    for (int i = 0; i < sides.size(); i++) {
        for (int j = 0; j < sides.at(i).size(); j++) {
            if (j == 0) {
                Vertex v1 = Vertex(sides.at(i).at(j+1).getX() - sides.at(i).at(j).getX(), sides.at(i).at(j+1).getY() - sides.at(i).at(j).getY(), sides.at(i).at(j+1).getZ() - sides.at(i).at(j).getZ());
                Vertex v2 = Vertex(sides.at(i).at(j+2).getX() - sides.at(i).at(j).getX(), sides.at(i).at(j+2).getY() - sides.at(i).at(j).getY(), sides.at(i).at(j+2).getZ() - sides.at(i).at(j).getZ());
                Vertex cross = Vertex(v1.getY() * v2.getZ() - v1.getZ() * v2.getY(), v1.getZ() * v2.getX() - v1.getX() * v2.getZ(), v1.getX() * v2.getY() - v1.getY() * v2.getX());
                (*normalsTemp).push_back(Vertex(cross.getX() / std::sqrt(cross.getX() * cross.getX() + cross.getY() * cross.getY() + cross.getZ() * cross.getZ()),
                    cross.getY() / std::sqrt(cross.getX() * cross.getX() + cross.getY() * cross.getY() + cross.getZ() * cross.getZ()),
                    cross.getZ() / std::sqrt(cross.getX() * cross.getX() + cross.getY() * cross.getY() + cross.getZ() * cross.getZ())));
            }
        }
    }
    normals.swap(*normalsTemp);
    delete normalsTemp;
    normalsTemp = nullptr;
}

//For angle between normal and xy axis, arccos(|a dot b|/|a||b|-pi/2)