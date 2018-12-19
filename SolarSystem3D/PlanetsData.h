#pragma once
#include "ConcretePlanet.h"
struct radiusOfPlanets {
	double sun = 696000;
	double mercury = 2439.5;
	double venus = 6051.8;
	double earth = 6378.1;
	double mars = 3396.2;
	double jupiter = 71492;
	double saturn = 60268;
	double uranus = 25559;
	double neptune = 24764;
};

struct radiusOfMoons {
	double moon = 1737.5;
	double marsFobos = 11.1;
	double marsDeimos = 6.2;
	double jupiterLo = 1530;
	double jupiterEuropa = 1500;
	double jupiterGanimedes = 2600;
	double saturnMimas = 190;
	double saturnEnceladus = 249;
	double saturnTetyda = 500;
	double uranusAriel = 530;
	double uranusUmbriel = 543;
	double neptuneTryton = 1350;
	double neptuneNereida = 170;
};

struct distanceMoonsFromPlanets {
	double moon = 384.4;
	double marsFobos = 9.4;
	double marsDeimos = 23.5;
	double jupiterLo = 422;
	double jupiterEuropa = 671;
	double jupiterGanimedes = 1070;
	double saturnMimas = 185;
	double saturnEnceladus = 238;
	double saturnTetyda = 294;
	double uranusAriel = 191;
	double uranusUmbriel = 266;
	double neptuneTryton = 354.8;
	double neptuneNereida = 5513;
};

struct distanceFromTheSun {
	double mercury = 57909170;
	double venus = 108208926;
	double earth = 149597887;
	double mars = 227936637;
	double jupiter = 778412027;
	double saturn = 1426725;
	double uranus = 2870972;
	double neptune = 4498252;
};

struct speedOfThePlanets {
	double mercury = 47;
	double venus = 35;
	double earth = 29;
	double mars = 24;
	double jupiter = 13;
	double saturn = 10;
	double uranus = 6;
	double neptune = 5;
};

struct Planets {
	ConcretePlanet* mercury;
	ConcretePlanet* venus;
	ConcretePlanet* earth;
	ConcretePlanet* mars;
	ConcretePlanet* jupiter;
	ConcretePlanet* saturn;
	ConcretePlanet* uranus;
	ConcretePlanet* neptune;
};

/*struct anglesOfPlanetsMoons {
	double mercury = 0;
	double venus = 0;
	double earth = 0;
	double mars = 0;
	double jupiter = 0;
	double saturn = 0;
	double uranus = 0;
	double neptune = 0;

	double moon = 0;
	double marsFobos = 0;
	double marsDeimos = 0;
	double jupiterLo = 0;
	double jupiterEuropa = 0;
	double jupiterGanimedes = 0;
	double saturnMimas = 0;
	double saturnEnceladus = 0;
	double saturnTetyda = 0;
	double uranusAriel = 0;
	double uranusUmbriel = 0;
	double neptuneTryton = 0;
	double neptuneNereida = 0;
};
*/

