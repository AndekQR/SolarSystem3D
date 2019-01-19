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

//sun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune
void ConcretePlanet::chooseTexture() {
	if (namePlanet.compare("sun") == 0)
		textureManager->BindTexture(tex[0]);
	else if (namePlanet.compare("mercury") == 0)
		textureManager->BindTexture(tex[1]);
	else if (namePlanet.compare("venus") == 0)
		textureManager->BindTexture(tex[2]);
	else if (namePlanet.compare("earth") == 0)
		textureManager->BindTexture(tex[3]);
	else if (namePlanet.compare("mars") == 0)
		textureManager->BindTexture(tex[4]);
	else if (namePlanet.compare("jupiter") == 0)
		textureManager->BindTexture(tex[5]);
	else if (namePlanet.compare("saturn") == 0)
		textureManager->BindTexture(tex[6]);
	else if (namePlanet.compare("uranus") == 0)
		textureManager->BindTexture(tex[7]);
	else if (namePlanet.compare("neptune") == 0)
		textureManager->BindTexture(tex[8]);
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

	chooseTexture();

	glPushMatrix();
	
	glRotated(angle, 0, 1, 0);
	glRotated(270, 1, 0, 0);

	glTranslated(distanceFromSun, 0, 0);
	gluSphere(quadric, radius, 100, 100);

	glBindTexture(GL_TEXTURE_2D, 0);
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
