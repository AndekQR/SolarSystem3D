#include "Move.hpp"
#include <iostream>


void Move::setPos(float inXPos, float inZPos) {
	initXPos = inXPos;
	xPos = inXPos;
	initZPos = inZPos;
	zPos = inZPos;

}

void Move::reset() {
	xPos = initXPos;
	zPos = initZPos;
	yPos = initYPos;
	angle = 0;
}

void Move::moveForward(bool move) {
	if (move) speed = 350.03f;
	else speed = 0;

}

void Move::moveBackward(bool move) {
	if (move) speed = -350.03f;
	else speed = 0;
}

void Move::turnLeft(bool move) {
	if (move) turn = 0.05f;
	else turn = 0;
}

void Move::turnRight(bool move) {
	if (move) turn = -0.05f;
	else turn = 0;
}

void Move::moveUp(bool move){
	if (move ) updown = 1000;
	else updown = 0;
}

//if (move->yPos > 400 && move->yPos < 413000)
void Move::moveDown(bool move){
	if (move && yPos > 7000) updown = -1000;
	else updown = 0;
}


Move::Move()
{
}


Move::~Move()
{
}
