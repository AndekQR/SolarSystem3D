#include <stdlib.h>
#include <gl/glut.h>
#include <math.h>
#include "Move.hpp"

#define ASPECT_1_1 1

Move move;
bool isMazeIsDrawn = false;

GLfloat alfa = 0.1;
GLfloat beta = 0.2;


void display() {
	

	move.angle = move.angle + move.turn;

	//Update the camera position based on the current camera speeds
	move.xPos = move.xPos + move.speed * sin(move.angle);
	move.zPos = move.zPos + move.speed * cos(move.angle);

	//update the look-at position based on the current cam position
	move.xLookAt = (float)(move.xPos + sin(move.angle));
	move.zLookAt = (float)(move.zPos + cos(move.angle));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyszczenie buforu koloru i z-buforu
	
	glClearColor(1.0, 1.0, 1.0, 1.0); //bialy
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(move.xPos, 0.5, move.zPos, move.xLookAt, 0.5, move.zLookAt, 0, 1, 0);
	//gluLookAt(move.xPos, 10, move.zPos, move.xLookAt, 0.5, move.zLookAt, 0, 1, 0); //widok z gory

	// kolor kraw�dzi sze�cianu
	//glColor3f(0.0, 0.0, 0.0);

	//glutWireCube(10);

	glColor3f(1, 1, 0);
	glutSolidSphere(5, 12, 12);
	glRotatef(alfa, 0, 1, 0);
	glTranslatef(40, 0, 0);
	glColor3f(0, 0, 1);
	glutSolidSphere(3, 12, 12);
	glRotatef(beta, 0, 1, 0);
	glTranslatef(10, 0, 0);
	glColor3f(0.5, 0.5, 0.5);
	glutSolidSphere(1, 12, 12);

	
	/*
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(0, 0, 0);
		glVertex3f(100, 0, 0);
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 100, 0);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 100);
	glEnd();
	*/
	glFlush();
	glutSwapBuffers();

}

void obroty() {
	alfa = alfa + 0.1;
	beta = beta + 0.1;
	glutPostRedisplay();
}

void reshape(int width, int height) {
	/*
	glViewport(0, 0, width, height); //obszar renderingu ca�e okno

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (ASPECT_1_1 == 1) { //parametry bry�y obcinania
		if (width >= height && height>0) {
			glFrustum(-2.0 * width / height, 2.0 * width / height, -2.0, 2.0, 1.0, 5.0);
		}
		else {
			if (height > width && width>0) {
				glFrustum(-2.0, 2.0, -2.0 * height / width, 2.0 * height / width, 1.0, 5.0);
			}
		}
	}
	else {
		glFrustum(-2.0, 2.0, -2.0, 2.0, 1.0, 5.0);
	}

	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 0.01, 100);
	

	display();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 0x1b:
		exit(0);
		break;
	default:
		break;
	}
}

void specialKeys(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		move.moveForward(true);
		display();
		break;
	case GLUT_KEY_DOWN:
		move.moveBackward(true);
		display();
		break;
	case GLUT_KEY_LEFT:
		move.turnLeft(true);
		display();
		break;
	case GLUT_KEY_RIGHT:
		move.turnRight(true);
		display();
		break;
	default:
		break;
	}
}

void specialUpKeys(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		move.moveForward(false);
		break;
	case GLUT_KEY_DOWN:
		move.moveBackward(false);
		break;
	case GLUT_KEY_LEFT:
		move.turnLeft(false);
		break;
	case GLUT_KEY_RIGHT:
		move.turnRight(false);
		break;
	default:
		break;
	}
}

void mouseMotion(int x, int y) {

}

void mouseButton(int button, int state, int x, int y) {

}





int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //podwojne buforowanie, ostatni parametr do z-bufora
	glutInitWindowSize(600, 600);
	glutCreateWindow("Maze3D");
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseButton); //obsluga przyciskow myszy
	glutMotionFunc(mouseMotion); //obsluga ruchu myszki
	glutSpecialFunc(specialKeys); //strzalki
	glutSpecialUpFunc(specialUpKeys);//obsluga puszczenia klawiszy 
	glutIdleFunc(obroty); //obroty w tle

	glEnable(GL_DEPTH_TEST);//wlaczenie bufora z
	//glDepthFunc(GL_GEQUAL);
	//glDepthRange(0, 0.1);
	

	glutMainLoop();

	return(0);
}
