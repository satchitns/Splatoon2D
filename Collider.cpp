/**************************************************************************************************
Title:			Collider.cpp
Written By:		Siddhant Ravi
Description:	This file defines the methods in the Collider class that is used in Splatoon 2D.
**************************************************************************************************/

#include <math.h>

#include "baseTypes.h"
#include "Collider.h"

/**************************************************************************************************
init

This function is used to initialize the collider by using the parameters to assign values to the
centre and the half size of the collider.
Inputs: 4 floats - the x and y value for the collider centre, the x and y value for the half size
Returns: none
**************************************************************************************************/
void Collider::init(float colliderCentreX, float colliderCentreY, float halfSizeX, float halfSizeY)
{
	setColliderCentre(colliderCentreX, colliderCentreY);															//initialize the collider centre
	setColliderHalfSize((colliderCentreX + halfSizeX), (colliderCentreY + halfSizeY));								//initialize the collider half size
}

/**************************************************************************************************
updateCollider

This function is used to update the collider by using the parameters to assign values to the
centre and the half size of the collider.
Inputs: 4 floats - the x and y value for the collider centre, the x and y value for the half size
Returns: none
**************************************************************************************************/
void Collider::updateCollider(float colliderCentreX, float colliderCentreY, float halfSizeX, float halfSizeY)
{
	setColliderCentre(colliderCentreX, colliderCentreY);															//update the collider centre
	setColliderHalfSize((halfSizeX), (halfSizeY));																	//update the collider half size
}

/**************************************************************************************************
detectCollision

This function is called to check whether the two objects whose Colliders are passed as arguments are
colliding.
Inputs: the Collider of the object calling this function and the the Collider of the object with
		which possibility of collision is to be checked
Returns: a Coord2D (x, y) that defines the push that the objects will receive if they collide.
		 Returns a (0, 0) if there is no collision, meaning there will be no push back.
**************************************************************************************************/
Coord2D Collider::detectCollision(Collider thisCollider, Collider otherCollider)
{
	Coord2D offset = { 0, 0 };		//Coord2D to store the amount by which the colliding objects will be offset

	float deltaX = (thisCollider.getColliderCentre().x - otherCollider.getColliderCentre().x);								//calculate the distance between the centres of the two colliders in the x direction
	float deltaY = (thisCollider.getColliderCentre().y - otherCollider.getColliderCentre().y);								//calculate the distance between the centres of the two colliders in the y direction

	float intersectX = (fabs(deltaX) - (thisCollider.getColliderHalfSize().x + otherCollider.getColliderHalfSize().x));		//subtract the absolute of the delta calculated above with the sum of the half sizes
	float intersectY = (fabs(deltaY) - (thisCollider.getColliderHalfSize().y + otherCollider.getColliderHalfSize().y));		//of both colliders in the x and y directions

	if ((intersectX < 0.0f) && (intersectY < 0.0f))					//if both the intersects calculated above are negative, then a collision has occurred
	{
		if (intersectX > intersectY)								//if the x intersect is greater than y intersect, then the objects are pushed apart in the x direction
		{
			if (deltaX > 0.0f)										//if the delta is positive then
			{
				offset.x = intersectX * COLLISION_PUSH;				//this object is pushed in the positive x direction (and the other object is pushed in the negative x direction)
			}
			else													//if the delta is non-positive
			{
				offset.x = -intersectX * COLLISION_PUSH;			//this object is pushed in the negative x direction (and the other object is pushed in the positive x direction)
			}
		}
		else														//if the y intersect is greater than the x intersect, then the objects are pushed in the y direction
		{
			if (intersectY >= intersectX)
			{
				if (deltaY > 0.0f)									//if the delta is positive then
				{
					offset.y = intersectY * COLLISION_PUSH;			//this object is pushed in the positive y direction (and the other object is pushed in the negative y direction)
				}
				else												//if the delta is non-positive
				{
					offset.y = -intersectY * COLLISION_PUSH;		//this object is pushed in the negative y direction (and the other object is pushed in the positive y direction)
				}
			}
		}

		return offset;
	}

	return offset;
}