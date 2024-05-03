#include <GL/glut.h>
#include "GLOBAL.h"
#include "Vertex.h"
#include "Shape.h"

//Vars
float z = 0;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Vertex tPoints[] = {
		Vertex(-1, 0, z),
		Vertex(1, 0, z),
		Vertex(0, 1, z)
	};
	Vertex* tPointStart = &tPoints[0];
	Shape triangle(tPointStart, sizeof(tPoints) / sizeof(tPoints[0]));
	triangle.draw();
	glFlush();
}

void keyPressed(unsigned char key, int x, int y) {
	if (key == 'w') {
		z += 0.1;
	}
	if (key == 's') {
		z -= 0.1;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	ShowWindow(GetConsoleWindow(), SW_HIDE); //Hide console
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(INITIAL_WINDOW_X, INITIAL_WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("GL");
	glClearColor(0.0, 0.0, 0.0, 0.0); //Black backgroud
	glMatrixMode(GL_PROJECTION); //Setup viewing projection
	glLoadIdentity(); //Start with identity matrix
	glOrtho(0.0, WIDTH, 0.0, HEIGHT, -DEPTH, 0.0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPressed);
	glutMouseFunc() //TODO MOUSE FUNCS
	glTranslatef(WIDTH / 2, HEIGHT / 2, 0);
	glutMainLoop();
	return 0;
}