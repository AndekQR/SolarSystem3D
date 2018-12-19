#pragma once

#include <string>
#include <GL/glut.h>
#include "PlanetsData.h"
#include "ConcretePlanet.h"

class DrawSolarSystem {
private:

public:
	void drawPlanets(struct Planets* planets);

	DrawSolarSystem();
	~DrawSolarSystem();
};

