#include <GL/glut.h>
#include "GLOBAL.h"
#include "PVector.h"
#include <iostream>

float sphereSDF(PVector v) {
    //std::cout << (sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2])) << std::endl;
    if (v.getMagnitude() - 300 < 0) {
        getColour();
        v.drawGlPVector();
    }
    return v.getMagnitude() - 300;
}

PVector normalise(PVector v) {
    return PVector(
        sphereSDF(PVector(v.getX() + 0.01, v.getY(), v.getZ())) - sphereSDF(PVector(v.getX() - 0.01, v.getY(), v.getZ())),
        sphereSDF(PVector(v.getX(), v.getY() + 0.01, v.getZ())) - sphereSDF(PVector(v.getX(), v.getY() - 0.01, v.getZ())),
        sphereSDF(PVector(v.getX(), v.getY(), v.getZ() + 0.01)) - sphereSDF(PVector(v.getX(), v.getY(), v.getZ() - 0.01))
    );
}

void getColour() {

}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (int i = -WIDTH/2; i <= WIDTH/2; i++) {
        for (int j = -HEIGHT/2; j <= HEIGHT/2; j++) {
            PVector pos( i, j, 0 );
            sphereSDF(pos);
        }
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    //ShowWindow(GetConsoleWindow(), SW_HIDE); //Hide console
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - WINDOW_WIDTH / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - WINDOW_HEIGHT / 2);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("GL");
    glClearColor(0.416, 0.353, 0.804, 0); //Black backgroud
    glMatrixMode(GL_MODELVIEW); //Setup viewing projection
    glLoadIdentity(); //Start with identity matrix
    glOrtho(0.0, WIDTH, 0.0, HEIGHT, 0.0, DEPTH);
    glutDisplayFunc(display);
    //glutKeyboardFunc(keyPressed);
    glTranslatef(WIDTH / 2, HEIGHT / 2, 0);
    glutMainLoop();
    return 0;
}