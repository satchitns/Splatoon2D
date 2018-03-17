/**************************************************************************************************
Title:			Collider.h
Written By:		Siddhant Ravi
Description:	This file declares the Collider class that is used in Splatoon 2D.
**************************************************************************************************/

#pragma once

#define COLLISION_PUSH 0.05f		//the slight push that the two colliding objects will experience

/**************************************************************************************************
Collider

The Collider class contains the definition of 2D colliders that is applied to players by adding an
instance of this class as a member and initializing it with appropriate values. The colliders are
axis aligned bounding boxes.
**************************************************************************************************/
class Collider
{
public:

	void init(float colliderCentreX, float colliderCentreY, float halfSizeX, float halfSizeY);					//method to initialize the collider
	
	void updateCollider(float colliderCentreX, float colliderCentreY, float halfSizeX, float halfSizeY);		//method to update the collider
	
	Coord2D detectCollision(Collider thisCollider, Collider otherCollider);										//method to detect collision between two colliders

	void setColliderCentre(float x, float y) { mColliderCentre = { x, y }; }									//method to set the collider center
	Coord2D getColliderCentre() { return mColliderCentre; }														//method to get the collider center
	
	void setColliderHalfSize(float x, float y) { mColliderHalfSize = { x, y }; }								//method to set the collider half size
	Coord2D getColliderHalfSize() { return mColliderHalfSize; }													//method to get the collider half size

private:

	Coord2D mColliderCentre;																					//a 2D vector that stores the center of the collider
	Coord2D mColliderHalfSize;																					//a 2D vector that stores the half size of the collider
};