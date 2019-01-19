#include "DrawSolarSystem.h"


void DrawSolarSystem::drawPlanets(struct Planets* planets) {
	planets->sun->draw();
	planets->mercury->draw();
	planets->venus->draw();
	planets->earth->draw();
	planets->mars->draw();
	planets->jupiter->draw();
	planets->saturn->draw();
	planets->uranus->draw();
	planets->neptune->draw();


	
}

DrawSolarSystem::DrawSolarSystem() {

}


DrawSolarSystem::~DrawSolarSystem() {

}
