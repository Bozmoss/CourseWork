#include <GL/glut.h>
#include "GLOBAL.h"
#include "Cube.h"

//Vars
float z = 0, ax = 0, ay = 0;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Cube cubes[] = {
        Cube(2, 2, 0, 0.5),
        //Cube(-2, -2, 0, 1),
        //Cube(0, 0, 0, 1)
    };
    for (Cube c : cubes) {
        c.draw(ax, ay);
    }
	glFlush();
}

void keyPressed(unsigned char key, int x, int y) {
	if (key == 'w') {
		ax -= 0.1;
	}
	if (key == 's') {
		ax += 0.1;
	}
	if (key == 'd') {
		ay += 0.1;
	}
	if (key == 'a') {
		ay -= 0.1;
	}
	glutPostRedisplay();
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
	glutKeyboardFunc(keyPressed);
	glTranslatef(WIDTH / 2, HEIGHT / 2, 0);
	glutMainLoop();
	return 0;
}