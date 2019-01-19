#pragma once

#include <GL/glut.h>
#include <vector>
#include "TextureManager.h"
#include <iostream>
#include <string>

class ConcretePlanet {
private:

	TextureManager* textureManager;
	GLuint* tex;
	GLUquadricObj* quadric = NULL;

	bool isThereElipseCoord = false;
	double radius;
	double distanceFromSun;
	double angle = 0;
	double valueToIncrementAngle;
	GLdouble modelViewMatrix[16];
	int elipseRadius = 0;
	std::string namePlanet;

	void loadTextures();
public:
	void init(TextureManager* textureManager, GLuint* tex);
	double x, z;
	void setRadiusOfElipse(int radius);
	std::vector <double> xCoord;
	std::vector <double> zCoord;
	void draw();

	ConcretePlanet(std::string planet, double radius, double distanceFromSun, double valueToIncrementAngle);
	~ConcretePlanet();
};

