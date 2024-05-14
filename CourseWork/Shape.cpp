#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <iterator>
#include <list>
#include <cmath>
#include <iostream>
#include "Shape.h"

void Shape::draw() {
    normals();
    list<Vector3>::iterator it;
    for (it1 = sides.begin(), it = sideNormals.begin(); it1 != sides.end(); it1++, it++) {
        //if ((*it).j() > 0) {
            glBegin(GL_QUADS);
            for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++) {
                (*it2).getProjectedVertex().drawGlVertex();
            }
            glEnd();
        //}                                               //TODO: SEND A LINE FROM EACH FACE TOWARDS THE OBSERVER AND IF THE LINE PASSES THROUGH ANOTHER SIDE DO NOT RENDER THE FACE
	}
}

void Shape::rotate(float ax, float ay) {
	list<list<Vertex>> temp;
	for (it1 = sides.begin(); it1 != sides.end(); it1++) {
		list<Vertex> temp1;
		for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++) {
			temp1.push_back((*it2).rotate(ax, ay));
		}
		temp.push_back(temp1);
	}
	sides.clear();
	for (it1 = temp.begin(); it1 != temp.end(); it1++) {
		list<Vertex> side;
		for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++) {
			side.push_back((*it2));
		}
		sides.push_back(side);
	}
}

void Shape::normals() {
    for (it1 = sides.begin(); it1 != sides.end(); it1++) {
        list<Vertex> current = (*it1);
        it2 = current.begin();
        Vector3 v1((*it2), (*it2++));
        Vector3 v2((*it2++), (*it2++));
        Vector3 cross = v1.crossProduct(v2);
        sideNormals.push_back(cross.scale(cross.modulus()));
    }
}