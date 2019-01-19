#include "ConcretePlanet.h"


void ConcretePlanet::loadTextures()
{
	quadric = gluNewQuadric();         // Create A Pointer To The Quadric Object
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricTexture(quadric, GL_TRUE);      // Create Texture Coords   
	gluQuadricNormals(quadric, GLU_SMOOTH);   // Create Smooth Normals  
}

void ConcretePlanet::init(TextureManager* textureManager, GLuint* tex)
{
	this->textureManager = textureManager;
	this->tex = tex;
}

void ConcretePlanet::setRadiusOfElipse(int radius)
{
	elipseRadius = radius;
}

void ConcretePlanet::draw() {
	if (angle<360) {
		angle = angle + valueToIncrementAngle;
	}
	else {
		angle = 0;
	}

	for (int i = 0; i <= 1000; i += 1) //rysowanie kola
	{

		if (!isThereElipseCoord) {
			x = elipseRadius * cos(i);
			z = elipseRadius * sin(i);

			xCoord.push_back(x);
			zCoord.push_back(z);
			//std::cout << xCoord[i] << ", " << zCoord[i] << std::endl;
		}

		
		glBegin(GL_POINTS);
		glVertex3f(xCoord[i], 0, zCoord[i]);
		glEnd();
	}
	isThereElipseCoord = true;

	if (namePlanet.compare("sun") == 0)
		textureManager->BindTexture(tex[0]);

	glPushMatrix();
	
	glRotated(angle, 0, 1, 0);
	glTranslated(distanceFromSun, 0, 0);
	//glutSolidSphere(radius, 50, 50);
	gluSphere(quadric, radius, 100, 100);

	glPopMatrix();
}





ConcretePlanet::ConcretePlanet(std::string planet, double radius, double distanceFromSun, double valueToIncrementAngle) {
	loadTextures();

	this->namePlanet = planet;
	this->radius = radius;
	this->distanceFromSun = distanceFromSun;
	this->valueToIncrementAngle = valueToIncrementAngle;

}



ConcretePlanet::~ConcretePlanet() {
}
