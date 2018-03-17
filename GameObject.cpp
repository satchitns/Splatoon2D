#include "GameObject.h"
#include "baseTypes.h"

void GameObject::setPosition(float_t xPosition, float_t yPosition)
{
	mPosition.x = xPosition;
	mPosition.y = yPosition;
}

void GameObject::setVelocity(float_t xVelocity, float_t yVelocity)
{
	mVelocity.x = xVelocity;
	mVelocity.y = yVelocity;
}

Coord2D* GameObject::getPosition()
{
	return &mPosition;
}

Coord2D* GameObject::getVelocity()
{
	return &mVelocity;
}