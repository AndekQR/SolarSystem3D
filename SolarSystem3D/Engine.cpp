#include <stdlib.h>
#include <iostream>
#include <gl/glut.h>
#include <math.h>
#include "Move.hpp"
#include "DrawSolarSystem.h"
#include "ConcretePlanet.h"
#include "PlanetsData.h"
#include "TextureManager.h"

#define ASPECT_1_1 1

#define FPS 50

#define radiusPlanetDivider 10
#define radiusMoonsDivider 
#define distanceMoonPlanetDivider
#define distancePlanetSunDivider 10
#define speedPlanetDivider 50




struct widok {
	bool widokZGory = true;
	bool widokZNadSlonca = false;
	bool widokMercury = false;
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
TextureManager* textureManager;
GLuint tex[9];

int i = 0;
double xFollowCamera;
double zFollowCamera;

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyszczenie buforu koloru i z-buforu
	
	glClearColor(0, 0, 0, 1.0); //czarny
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	

	if(view->widokZGory)
		gluLookAt(move->xPos, move->yPos, move->zPos, move->xLookAt, 5000, move->zLookAt, 0, 1, 0);
	else if(view->widokZNadSlonca)
		gluLookAt(move->xPos, move->yPos, move->zPos, move->xLookAt, 5000, move->zLookAt, 0, 1, 0);
	else if (view->widokMercury) {
		gluLookAt(planets->mercury->xCoord[i], move->yPos, planets->mercury->zCoord[i], planets->mercury->xCoord[i], 5000, planets->mercury->zCoord[i], 0, 1, 0);
	}

	for (auto i : planets->mercury->xCoord) {
		std::cout << i << std::endl;
	}
		

	//i = i + 100; //fajny widok!
	//gluLookAt(planets->mercury->x + i, move->yPos, planets->mercury->z + i, planets->mercury->x, 0, planets->mercury->z, 0, 1, 0);
	
	//gluLookAt(0, 15000, 0, 10000, 5000, 14000, 0, 1, 0);
	
	//gluLookAt(move->xPos, 15000, move->zPos, move->xLookAt, 5000, move->zLookAt, 0, 1, 0);


	drawing->drawPlanets(planets);

	
	glutSwapBuffers();

}



void timer(int val) {

	move->angle = move->angle + move->turn;

	//aktualizacja pozycji kamery na podstawie prêdkoœci kamery
	move->xPos = move->xPos + move->speed * sin(move->angle);
	move->zPos = move->zPos + move->speed * cos(move->angle);
	move->yPos = move->yPos + move->updown;

	

	//std::cout << move->yPos << std::endl;

	//aktualizacja kierunku patrzenia kamery na podstawie jej pozycji
	move->xLookAt = (float)(move->xPos + sin(move->angle));
	move->zLookAt = (float)(move->zPos + cos(move->angle));


	i = i + 1;
	if (i == 999)
		i = 0;
	xFollowCamera = planets->mercury->xCoord[i] + cos(move->angle)*(1000);
	zFollowCamera = planets->mercury->zCoord[i] + cos(move->angle)*(1000);

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
void setRadiusElipseOfPlanets() {
	planets->mercury->setRadiusOfElipse(distancePlanetSun->mercury / 7000);
	planets->venus->setRadiusOfElipse(distancePlanetSun->venus / 7000);
	planets->earth->setRadiusOfElipse(distancePlanetSun->earth / 7000);
	planets->mars->setRadiusOfElipse(distancePlanetSun->mars / 7000);
	planets->jupiter->setRadiusOfElipse(distancePlanetSun->jupiter / 7000);
	planets->saturn->setRadiusOfElipse(distancePlanetSun->saturn / 25000);
	planets->uranus->setRadiusOfElipse(distancePlanetSun->uranus / 23000);
	planets->neptune->setRadiusOfElipse(distancePlanetSun->neptune / 25000);
}

void createPlanets() {
	planets->mercury = new ConcretePlanet("mercury", planetsRadius->mercury/radiusPlanetDivider , distancePlanetSun->mercury /7000, speedPlanet->mercury / speedPlanetDivider);
	planets->mercury->init(textureManager, tex);
	
	planets->venus = new ConcretePlanet("venus", planetsRadius->venus / radiusPlanetDivider, distancePlanetSun->venus / 7000, speedPlanet->venus / speedPlanetDivider);
	planets->venus->init(textureManager, tex);
	
	planets->earth = new ConcretePlanet("earth", planetsRadius->earth / radiusPlanetDivider, distancePlanetSun->earth/ 7000, speedPlanet->earth / speedPlanetDivider);
	planets->earth->init(textureManager, tex);
	
	planets->mars= new ConcretePlanet("mars", planetsRadius->mars / radiusPlanetDivider, distancePlanetSun->mars/ 7000, speedPlanet->mars / speedPlanetDivider);
	planets->mars->init(textureManager, tex);
	
	planets->jupiter= new ConcretePlanet("jupiter", planetsRadius->jupiter / 20, distancePlanetSun->jupiter / 7000, speedPlanet->jupiter / speedPlanetDivider);
	planets->jupiter->init(textureManager, tex);
	
	planets->saturn= new ConcretePlanet("saturn", planetsRadius->saturn / 30, distancePlanetSun->saturn / 25000, speedPlanet->saturn / speedPlanetDivider);
	planets->saturn->init(textureManager, tex);
	
	planets->uranus= new ConcretePlanet("uranus", planetsRadius->uranus / 25, distancePlanetSun->uranus / 23000, speedPlanet->uranus / speedPlanetDivider);
	planets->uranus->init(textureManager, tex);

	planets->neptune= new ConcretePlanet("neptune", planetsRadius->neptune / 25, distancePlanetSun->neptune / 25000, speedPlanet->neptune / speedPlanetDivider);
	planets->neptune->init(textureManager, tex);
	
	planets->sun = new ConcretePlanet("sun", planetsRadius->sun / 150, 0, 0);
	planets->sun->init(textureManager, tex);

	setRadiusElipseOfPlanets();
}



void setAllViewsToFalse() {
	view->widokZGory = false;
	view->widokZNadSlonca = false;
}

void menu(int num) {
	switch (num) {
	case 1:
		setAllViewsToFalse();
		move->yPos = 15000;
		move->initYPos = 15000;
		view->widokZGory = true;
		break;
	case 2:
		setAllViewsToFalse();
		move->yPos = 5000;
		move->initYPos = 5000;
		view->widokZNadSlonca = true;
		break;
	case 3:
		move->reset();
		break;
	case 4:
		setAllViewsToFalse();
		view->widokMercury = true;
		break;
	}

	glutPostRedisplay();
}

void createMenu(void) {
	int submenu1 = glutCreateMenu(menu);
	glutAddMenuEntry("Widok z gory", 1);
	glutAddMenuEntry("Widok z nad slonca", 2);
	glutAddMenuEntry("Widok na planete merkury", 4);
	glutAddMenuEntry("Reset", 3);


	glutCreateMenu(NULL);
	glutAddSubMenu("Widok", submenu1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void loadTextures() {
	glGenTextures(9, tex);
	//sun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune
	textureManager->LoadTexture("sun.jpg", tex[0]);
	textureManager->LoadTexture("mercury.jpg", tex[1]);
	textureManager->LoadTexture("venus.jpg", tex[2]);
	textureManager->LoadTexture("earth.jpg", tex[3]);
	textureManager->LoadTexture("mars.jpg", tex[4]);
	textureManager->LoadTexture("jupiter.jpg", tex[5]);
	textureManager->LoadTexture("saturn.jpg", tex[6]);
	textureManager->LoadTexture("uranus.jpg", tex[7]);
	textureManager->LoadTexture("neptune.jpg", tex[8]);
	
}



int main(int argc, char *argv[]) {


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //podwojne buforowanie, ostatni parametr do z-bufora
	

	



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

	glEnable(GL_DEPTH_TEST);//wlaczenie bufora z
	glEnable(GL_TEXTURE_2D); //w³¹czenie teksturowania

	textureManager = TextureManager::Inst();
	loadTextures();

	initializeDataOfPlanets();
	planets = new Planets; //struktura z planetami w planetsData.h
	createPlanets();
	drawing = new DrawSolarSystem();

	move = new Move();

	view = new widok;

	createMenu();

	glutTimerFunc(1000 / FPS, timer, 0); //timer
	glutMainLoop();



//-------------------------------------------------------------------------------
	textureManager->UnloadAllTextures();

	delete planetsRadius;
	delete moonsRadius;
	delete distanceMoonPlanet;
	delete distancePlanetSun;
	delete speedPlanet;
	delete planets;

	return(0);
}
