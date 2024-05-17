#include <GL/glut.h>
#include "GLOBAL.h"
#include "Vertex.h"
#include "Shape.h"

//Vars
float z = 0, ax = 0, ay = 0;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Vertex points[][4] = {
		{
			Vertex(-1, 1, 1),
			Vertex(1, 1, 1),
			Vertex(1, -1, 1),
			Vertex(-1, -1, 1)
},
		{
			Vertex(-1, 1, -1),
			Vertex(1, 1, -1),
			Vertex(1, -1, -1),
			Vertex(-1, -1, -1)
},
		{
			Vertex(1, 1, -1),
			Vertex(1, 1, 1),
			Vertex(1, -1, 1),
			Vertex(1, -1, -1)
},
		{
			Vertex(-1, 1, -1),
			Vertex(-1, 1, 1),
			Vertex(-1, -1, 1),
			Vertex(-1, -1, -1)
},
		{
			Vertex(-1, 1, -1),
			Vertex(1, 1, -1),
			Vertex(1, 1, 1),
			Vertex(-1, 1, 1)
},
		{
			Vertex(-1, -1, -1),
			Vertex(1, -1, -1),
			Vertex(1, -1, 1),
			Vertex(-1, -1, 1)
}
	};
	Vertex* pointStart = &points[0][0];
	Shape s(pointStart, sizeof(points) / sizeof(points[0]), sizeof(points[0]) / sizeof(points[0][0]));
	s.rotate(ax, ay);
	s.draw();
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
	glutInitWindowPosition(INITIAL_WINDOW_X, INITIAL_WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("GL");
	glClearColor(0.0, 0.0, 0.0, 0.0); //Black backgroud
	glMatrixMode(GL_PROJECTION); //Setup viewing projection
	glLoadIdentity(); //Start with identity matrix
	glOrtho(0.0, WIDTH, 0.0, HEIGHT, -DEPTH, 0.0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPressed);
	glTranslatef(WIDTH / 2, HEIGHT / 2, 0);
	glutMainLoop();
	return 0;
}