// Anything sprite, player, etc. in the game is derived from this class
// Any game object has a 2D position and velocity

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "baseTypes.h"

class GameObject
{

public:
	GameObject() {};
	~GameObject() {};

	void setPosition(float_t xPosition, float_t yPosition);
	void setVelocity(float_t xVelocity, float_t yVelocity);

	Coord2D* getPosition();
	Coord2D* getVelocity();

	virtual void render() = 0;

private:
	Coord2D mPosition;
	Coord2D mVelocity;

};

#endif