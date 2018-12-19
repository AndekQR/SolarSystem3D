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

Move* move; //ruch
DrawSolarSystem* drawing; //rysowanie planet

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

	gluLookAt(move->xPos, 0.5, move->zPos, move->xLookAt, 0.5, move->zLookAt, 0, 1, 0);
	//gluLookAt(move.xPos, 10, move.zPos, move.xLookAt, 0.5, move.zLookAt, 0, 1, 0); //widok z gory


	drawing->drawPlanets(planets);

	
/*	glBegin(GL_LINES);
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
	
	
	//glFlush();
	glutSwapBuffers();

}



void timer(int val) {

	move->angle = move->angle + move->turn;

	//aktualizacja pozycji kamery na podstawie prêdkoœci kamery
	move->xPos = move->xPos + move->speed * sin(move->angle);
	move->zPos = move->zPos + move->speed * cos(move->angle);

	//aktualizacja kierunku patrzenia kamery na podstawie jej pozycji
	move->xLookAt = (float)(move->xPos + sin(move->angle));
	move->zLookAt = (float)(move->zPos + cos(move->angle));

	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}

void reshape(int width, int height) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 0.01, 100000);
	

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
		move->moveForward(true);
		display();
		break;
	case GLUT_KEY_DOWN:
		move->moveBackward(true);
		display();
		break;
	case GLUT_KEY_LEFT:
		move->turnLeft(true);
		display();
		break;
	case GLUT_KEY_RIGHT:
		move->turnRight(true);
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
	planets->earth = new ConcretePlanet(planetsRadius->earth/100 , distancePlanetSun->earth/500000, speedPlanet->earth, 1);
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
	glutMouseFunc(mouseButton); //obsluga przyciskow myszy
	glutMotionFunc(mouseMotion); //obsluga ruchu myszki
	glutSpecialFunc(specialKeys); //strzalki
	glutSpecialUpFunc(specialUpKeys);//obsluga puszczenia klawiszy 
	glutTimerFunc(1000 / FPS, timer, 0); //timer



	move = new Move();
	move->setPos(200, 200);

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
