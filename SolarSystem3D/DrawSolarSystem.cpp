#include "DrawSolarSystem.h"


void DrawSolarSystem::drawPlanets(struct Planets* planets) {

	glColor3f(1, 1, 0);
	planets->mercury->draw();
	planets->venus->draw();
	planets->earth->draw();
	planets->mars->draw();
	planets->jupiter->draw();
	planets->saturn->draw();
	//planets->uranus->draw();
	//planets->neptune->draw();

}

DrawSolarSystem::DrawSolarSystem() {

}


DrawSolarSystem::~DrawSolarSystem() {

}
