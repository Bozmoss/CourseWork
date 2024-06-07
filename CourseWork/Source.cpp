#include <GL/glut.h>
#include "GLOBAL.h"
#include "PVector.h"

float sphereSDF(PVector p, float r) {
    return p.getMagnitude() - r;
}

PVector calcNormal(PVector pos) {
    const float EPS = 0.001;
    PVector v1 = PVector(
        sphereSDF(pos.add(PVector(EPS, 0.0, 0.0)), 1),
        sphereSDF(pos.add(PVector(0.0, EPS, 0.0)), 1),
        sphereSDF(pos.add(PVector(0.0, 0.0, EPS)), 1)
    );
    PVector v2 = PVector(
        sphereSDF(pos.add(PVector(-EPS, 0.0, 0.0)), 1),
        sphereSDF(pos.add(PVector(0.0, -EPS, 0.0)), 1),
        sphereSDF(pos.add(PVector(0.0, 0.0, -EPS)), 1)
    );
    v2.scale(-1);
    PVector v3 = v1.add(v2);
    v3.scale(v3.getMagnitude());
    return v3;
}

PVector rayMarch(PVector pos, PVector dir) {
    int step = 0;
    float d = sphereSDF(pos, 1);
    while (abs(d) > 0.001 && step < 50) {
        dir.scale(d);
        pos = PVector(pos.getX() + dir.getX(), pos.getY() + dir.getY(), pos.getZ() + dir.getZ());
        d = sphereSDF(pos, 1);
        step++;
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PVector dir(0, 0, -DEPTH);
    for (int i = 0; i < WINDOW_WIDTH; i++) {
        for (int j = 0; j < WINDOW_HEIGHT; j++) {
            for (int k = 0; k < DEPTH; k++) {
                PVector pos(i, j, k);
                pos = rayMarch(pos, dir);

            }
        }
    }
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