#pragma once
class Move
{
public:
	float xPos = 1, initXPos, xLookAt = 0;
	float zPos = 1, initZPos, zLookAt = 0;
	float yPos = 20000,  yLookAt = 0;
	float speed = 0;
	float angle = 3.9;
	float turn = 0;

	void setPos(float inXPos, float inZPos);
	void reset();
	void moveForward(bool move);
	void moveBackward(bool move);
	void turnLeft(bool move);
	void turnRight(bool move);
	void moveUp();
	void moveDown();

	Move();
	~Move();
};


