#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <iterator>
#include <list>
#include <cmath>
#include <iostream>
#include "Shape.h"

void Shape::draw() {
    checkSides();
    for (it1 = sides.begin(); it1 != sides.end(); it1++) {
        glBegin(GL_QUADS);
        for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++) {
            (*it2).getProjectedVertex().drawGlVertex();
        }
        glEnd();
	}
}

void Shape::rotate(float ax, float ay) {
	list<list<Vertex>> temp;
	for (it1 = sides.begin(); it1 != sides.end(); it1++) {
		list<Vertex> side;
		for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++) {
			side.push_back((*it2).rotate(ax, ay));
		}
		temp.push_back(side);
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

void Shape::checkSides() {
    list<list<Vertex>> temp;
    for (it1 = sides.begin(); it1 != sides.end(); it1++) {
        list<Vertex> side;
        for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++) {
            side.push_back((*it2).getProjectedVertex());
        }
        temp.push_back(side);
    }
    sides.clear();
    for (it1 = temp.begin(); it1 != temp.end(); it1++) {
        list<Vertex> side;
        for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++) {
            side.push_back((*it2));
        }
        sides.push_back(side);
    }
    //temp.clear();
    //temp = sort2DList(sides);
    for (it2 = sideCentres.begin(); it2 != sideCentres.end(); it2++) {
        for (it1 = temp.begin(); it1 != temp.end(); it1++) {
            list<Vertex>::iterator it;
            for (it = (*it1).begin(); it != (*it1).end(); it++) {
                //TODO: CHECK IF PROJECTED CENTRE IS IN THE BOUNDS OF ONE OF THE SIDES.
            }
        }
    }
}

list<list<Vertex>> Shape::sort2DList(list<list<Vertex>> l) {
/*    list<list<Vertex>> temp;
    for (it1 = l.begin(); it1 != l.end(); it1++) {
        list<Vertex> sorted = sortList((*it1), 0);
        temp.push_back(sorted);
    }
    return temp;*/
    return l;
}

list<Vertex> Shape::sortList(list<Vertex> l, int mode) {
/*    for (it2 = l.begin(); it2 != l.end()--; it2++) {
        list<Vertex>::iterator it;
        switch (mode) {
        case 0:
            for (it = l.begin()++; it != l.end()--; it++) {
                if ((*it).getX() > (*std::next(it)).getX()) {
                    std::swap(*it, *std::next(it));
                }
            }
            break;
        case 1:
            for (it = l.begin()++; it != l.end()--; it++) {
                if ((*it).getY() > (*std::next(it)).getY()) {
                    std::swap(*it, *std::next(it));
                }
            }
            break;
        }
    }
    return l;*/
    return l;
}