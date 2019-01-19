#pragma once
class Move
{
public:
	float xPos = 0, initXPos = 0, xLookAt = 0;
	float zPos = 0, initZPos = 0, zLookAt = 0;
	float yPos = 16000, initYPos = 16000;
	float speed = 0;
	float angle = 0;
	float turn = 0;
	float updown = 0;

	void setPos(float inXPos, float inZPos);
	void reset();
	void moveForward(bool move);
	void moveBackward(bool move);
	void turnLeft(bool move);
	void turnRight(bool move);
	void moveUp(bool move);
	void moveDown(bool move);

	Move();
	~Move();
};


