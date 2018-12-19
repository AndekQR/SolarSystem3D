#pragma once

#include <GL/glut.h>

class ConcretePlanet {
private:
	double radius;
	double distanceFromSun;
	double speed;
	double angle = 0;
	double valueToIncrementAngle;
public:
	void draw();
	ConcretePlanet(double radius, double distanceFromSun, double speed,  double valueToIncrementAngle);
	~ConcretePlanet();
};

