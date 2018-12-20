#include "ConcretePlanet.h"



void ConcretePlanet::draw() {
	if (angle<360) {
		angle = angle + valueToIncrementAngle;
	}
	else {
		angle = 0;
	}
	glPushMatrix();
	glRotated(angle, 0, 1, 0);
	glTranslated(distanceFromSun, 0, 0);
	glutSolidSphere(radius, 50, 50);
	glPopMatrix();
}

ConcretePlanet::ConcretePlanet(double radius, double distanceFromSun, double speed, double valueToIncrementAngle) {
	this->radius = radius;
	this->distanceFromSun = distanceFromSun;
	this->speed = speed;
	this->valueToIncrementAngle = valueToIncrementAngle;
}



ConcretePlanet::~ConcretePlanet() {
}
