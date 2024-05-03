#include <GL/glut.h>
#include "GLOBAL.h"
#include "Matrix3D.h"

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	float mat[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	Matrix3D(mat);
	glFlush();
}

void keys(int key, int x, int y) {
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	//ShowWindow(GetConsoleWindow(), SW_HIDE); //Hide console
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
	glutSpecialFunc(keys);
	glTranslatef(WIDTH/2, HEIGHT/2, 0);
	glutMainLoop();
	return 0;
}