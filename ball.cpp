#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "ShapeDraw.h"
#include "collInfo.h"
#include "object.h"
//#include "inputmapper.h"
#include "ball.h"
#include "field.h"
#include "fieldmanager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "stateManager.h"
#include "inputmanager.h"


void BallC::moveUp()
{
	int x;
	x=5;
}
BallC::BallC(float initPosX,float initPosY,float initVelX,float initVelY,int id)
{

	mPosition.x = initPosX;
	mPosition.y = initPosY;
	mVelocity.x = initVelX;
	mVelocity.y = initVelY;

}
BallC::BallC()
{
    mEnabled = true;
    mCollInfo.shape = CollInfoC::SHAPE_CIRCLE;

};
BallC::~BallC()
{
};

void BallC::update(DWORD milliseconds)
{
    mPosition.x += mVelocity.x*milliseconds/10;
    mPosition.y += mVelocity.y*milliseconds/10;

	DoCollisions();
}
void BallC::DoCollisions()
{
	CollideField();
}
void BallC::CollideField(void)
{
	FieldC *field = FieldManagerC::GetInstance()->getFieldPtr();

	float_t rightSide = field->getPosition()->x+((float_t)field->getWidth()/2.0f);
	float_t leftSide = field->getPosition()->x-((float_t)field->getWidth()/2.0f);
	float_t topSide = field->getPosition()->y+((float_t)field->getHeight()/2.0f);
	float_t bottomSide = field->getPosition()->y-((float_t)field->getHeight()/2.0f);
	
	if(mPosition.x- mRadius <= leftSide  )
	{
		mVelocity.x = -mVelocity.x;
		mPosition.x = leftSide + mRadius;
		setRandomColor();
	}
	if(mPosition.x+ mRadius >= rightSide  )
	{
		mVelocity.x = -mVelocity.x;
		mPosition.x = rightSide - mRadius;
		setRandomColor();
	}
	if(mPosition.y- mRadius <= bottomSide  )
	{
		mVelocity.y = -mVelocity.y;
		mPosition.y = bottomSide + mRadius;
		setRandomColor();
	}
	if(mPosition.y+ mRadius >= topSide  )
	{
		mVelocity.y = -mVelocity.y;
		mPosition.y = topSide - mRadius;
		setRandomColor();
	}
};
void BallC::render()
{
	char8_t red = (char8_t)((mBallColor>>16)& 0xFF);
	char8_t green = (char8_t)((mBallColor>>8) & 0xFF);
	char8_t blue = (char8_t)((mBallColor>>0) & 0xFF);
	bool filledVal;

	switch(StateManagerC::GetInstance()->getState())
	{
		case StateManagerC::ALL_BALLS_FILLED:
			filledVal = true;
			break;
		case StateManagerC::HALF_BALLS_FILLED:
			filledVal = (mID%2)?true:false;
			break;
		case StateManagerC::NO_BALLS_FILLED:
			filledVal = false;
			break;
	}
	DrawCircle(mRadius,mPosition.x,mPosition.y,red,green,blue,filledVal);
}
void BallC::setRandomColor()
{
	mBallColor = getRangedRandom(0,256);
	mBallColor += getRangedRandom(0,256) << 8;
	mBallColor += getRangedRandom(0,256) << 16;
}

