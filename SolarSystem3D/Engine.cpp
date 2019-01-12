#include <stdlib.h>
#include <iostream>
#include <gl/glut.h>
#include <math.h>
#include "Move.hpp"
#include "DrawSolarSystem.h"
#include "ConcretePlanet.h"
#include "PlanetsData.h"

#define ASPECT_1_1 1

#define FPS 50

#define radiusPlanetDivider 10
#define radiusMoonsDivider 
#define distanceMoonPlanetDivider
#define distancePlanetSunDivider 25000

struct widok {
	bool widokZGory = true;
	bool widokZNadSlonca = false;
};

Move* move; //ruch
DrawSolarSystem* drawing; //rysowanie planet
widok* view;

radiusOfPlanets* planetsRadius;
radiusOfMoons* moonsRadius;
distanceMoonsFromPlanets* distanceMoonPlanet;
distanceFromTheSun* distancePlanetSun;
speedOfThePlanets* speedPlanet;

Planets* planets; //struktura z obiektami planet

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyszczenie buforu koloru i z-buforu
	
	glClearColor(0, 0, 0, 1.0); //czarny
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if(view->widokZGory)
		gluLookAt(move->xPos, move->yPos, move->zPos, move->xLookAt, 5000, move->zLookAt, 0, 1, 0);
	else if(view->widokZNadSlonca)
		gluLookAt(move->xPos, 15000, move->zPos, 5000, 1000, 5000, 0, 1, 0);
	
	//gluLookAt(0, 15000, 0, 10000, 5000, 14000, 0, 1, 0);
	
	//gluLookAt(move->xPos, 15000, move->zPos, move->xLookAt, 5000, move->zLookAt, 0, 1, 0);


	drawing->drawPlanets(planets);

	
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
	
	
	
	//glFlush();
	glutSwapBuffers();

}



void timer(int val) {

	move->angle = move->angle + move->turn;

	//aktualizacja pozycji kamery na podstawie prêdkoœci kamery
	move->xPos = move->xPos + move->speed * sin(move->angle);
	move->zPos = move->zPos + move->speed * cos(move->angle);
	move->yPos = move->yPos + move->updown;

	//aktualizacja kierunku patrzenia kamery na podstawie jej pozycji
	move->xLookAt = (float)(move->xPos + sin(move->angle));
	move->zLookAt = (float)(move->zPos + cos(move->angle));

	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}

void reshape(int width, int height) {

	if (height == 0)	
		height = 1;

	glViewport(0, 0, width, height);

	/* Ustawienie obszaru obcinania z uwzglêdnieniem proporcji okna */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* Rzutowanie perspektywiczne */
	gluPerspective(50, (float)width / height, 0.01, 50000000000);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27: //esc
		exit(0);
		break;
	case 43://+
		move->moveUp(true);
		break;
	case 45://-
		move->moveDown(true);
		break;
	default:
		break;
	}
}

void keyboardUp(unsigned char key, int x, int y) {
	switch (key)
	{
	case 43://+
		move->moveUp(false);
		break;
	case 45://-
		move->moveDown(false);
		break;
	default:
		break;
	}
}

void specialKeys(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		move->moveForward(true);
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		move->moveBackward(true);
		glutPostRedisplay(); 
		break;
	case GLUT_KEY_LEFT:
		move->turnLeft(true);
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		move->turnRight(true);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void specialUpKeys(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		move->moveForward(false);
		break;
	case GLUT_KEY_DOWN:
		move->moveBackward(false);
		break;
	case GLUT_KEY_LEFT:
		move->turnLeft(false);
		break;
	case GLUT_KEY_RIGHT:
		move->turnRight(false);
		break;
	default:
		break;
	}
}

void mouseMotion(int x, int y) {

}

void mouseButton(int button, int state, int x, int y) {

}

void initializeDataOfPlanets() {
	planetsRadius = new radiusOfPlanets;
	moonsRadius = new radiusOfMoons;
	distanceMoonPlanet = new distanceMoonsFromPlanets;
	distancePlanetSun = new distanceFromTheSun;
	speedPlanet = new speedOfThePlanets;
}

void createPlanets() {
	planets->mercury = new ConcretePlanet(planetsRadius->mercury / radiusPlanetDivider, distancePlanetSun->mercury / distancePlanetSunDivider, speedPlanet->mercury, 1);
	planets->venus = new ConcretePlanet(planetsRadius->venus / radiusPlanetDivider, distancePlanetSun->venus / distancePlanetSunDivider, speedPlanet->venus, 1);
	planets->earth = new ConcretePlanet(planetsRadius->earth/ radiusPlanetDivider, distancePlanetSun->earth/ distancePlanetSunDivider, speedPlanet->earth, 1);
	planets->mars= new ConcretePlanet(planetsRadius->mars / radiusPlanetDivider, distancePlanetSun->mars / distancePlanetSunDivider, speedPlanet->mars, 1);
	planets->jupiter= new ConcretePlanet(planetsRadius->jupiter / radiusPlanetDivider, distancePlanetSun->jupiter / distancePlanetSunDivider, speedPlanet->jupiter, 1);
	planets->saturn= new ConcretePlanet(planetsRadius->saturn / radiusPlanetDivider, distancePlanetSun->saturn / distancePlanetSunDivider, speedPlanet->saturn, 1);
	planets->uranus= new ConcretePlanet(planetsRadius->uranus / radiusPlanetDivider, distancePlanetSun->uranus / distancePlanetSunDivider, speedPlanet->uranus, 1);
	planets->neptune= new ConcretePlanet(planetsRadius->neptune / radiusPlanetDivider, distancePlanetSun->neptune / distancePlanetSunDivider, speedPlanet->neptune, 1);
}

void setAllViewsToFalse() {
	view->widokZGory = false;
	view->widokZNadSlonca = false;
}

void menu(int num) {
	if (num == 1) {
		setAllViewsToFalse();
		view->widokZGory = true;
	}
	if (num == 2) {
		setAllViewsToFalse();
		view->widokZNadSlonca = true;
	}
	else {
		
	}
	glutPostRedisplay();
}

void createMenu(void) {
	int submenu1 = glutCreateMenu(menu);
	glutAddMenuEntry("Widok z gory", 1);
	glutAddMenuEntry("Widok z nad s³oñca", 2);


	int submenu7 = glutCreateMenu(menu);
	glutAddSubMenu("Widok", submenu1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}



int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //podwojne buforowanie, ostatni parametr do z-bufora
	
	initializeDataOfPlanets();
	planets = new Planets; //struktura z planetami
	createPlanets();
	drawing = new DrawSolarSystem();

	glutInitWindowSize(600, 600);
	glutCreateWindow("Maze3D");
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouseButton); //obsluga przyciskow myszy
	glutMotionFunc(mouseMotion); //obsluga ruchu myszki
	glutSpecialFunc(specialKeys); //strzalki
	glutSpecialUpFunc(specialUpKeys);//obsluga puszczenia klawiszy 
	view = new widok;
	createMenu();
	glutTimerFunc(1000 / FPS, timer, 0); //timer



	move = new Move();
	move->setPos(500, 500);

	glEnable(GL_DEPTH_TEST);//wlaczenie bufora z
	//glDepthFunc(GL_GEQUAL);
	//glDepthRange(0, 0.1);
	

	glutMainLoop();

	delete planetsRadius;
	delete moonsRadius;
	delete distanceMoonPlanet;
	delete distancePlanetSun;
	delete speedPlanet;
	delete planets;

	return(0);
}
