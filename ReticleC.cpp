
#include<windows.h>
#include "baseTypes.h"
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "SOIL.h"
#include "Utils.h"
#include "RenderSprites.h"
#include "ReticleC.h"
#include "game.h"



Coord2D ReticleC::offsetFromCenter = {(float)SIZE_X/2, (float)SIZE_Y/2};
Coord2D ReticleC::offsetBGFromCenter = { (float)BG_SIZE_X / 2, (float)BG_SIZE_Y / 2 };
ReticleC::ReticleC()
{
	mOffsetFromPlayer = { 0,0 };
}

void ReticleC::init(int ID, int playerPositionX, int playerPositionY, GLuint reticleTexID, GLuint reticleBGID)
{
	mID = ID;
	mSize.x = SIZE_X;
	mSize.y = SIZE_Y;
	mPosition.x = playerPositionX;
	mPosition.y = playerPositionY;
	mTexID = reticleTexID;
	mBGTexID = reticleBGID;
	switch (mID)
	{
	case 0:
		mRenderColor = { 0x01, 0x0B, 0x99, 0xff };
		break;
	case 1:
		mRenderColor = { 0xAD, 0x4C, 0x0F, 0xff };
		break;
	case 2:
		mRenderColor = { 0x0A, 0x7C, 0x00, 0xFF };
		break;
	case 3:
		mRenderColor = { 0x61, 0x02, 0x82, 0xFF };
		break;
	default:
		break;
	}
	mVibrated = false;
	vibration = new XINPUT_VIBRATION();
	mTimeVibrated = 0;
	SetReticleVibration(0, 0);

}

ReticleC::~ReticleC()
{
}

void ReticleC::SetPosition(DWORD milliseconds, float axisValueX, float axisValueY)
{
	mPosition.x += RETICLE_SPEED * milliseconds * axisValueX;
	mPosition.y += RETICLE_SPEED * milliseconds * axisValueY;
	vibration->wLeftMotorSpeed = 0;
	if (mVibrated)
	{
		mTimeVibrated += (float)milliseconds / 1000;
	}
}


void ReticleC::SetReticleVibration(WORD leftMotor, WORD rightMotor)
{
	vibration->wLeftMotorSpeed = leftMotor;
	vibration->wRightMotorSpeed = rightMotor;
}


void ReticleC::UpdateReticleOffset(Coord2D* playerPosition)
{
	mOffsetFromPlayer.x = mPosition.x - playerPosition->x;
	mOffsetFromPlayer.y = mPosition.y - playerPosition->y;

	if (fabs(sqrt(pow(mOffsetFromPlayer.x, 2) + pow(mOffsetFromPlayer.y, 2))) > MAX_RETICLE_OFFSET)
	{
		float reticleNormalizationFactor = 1 / (sqrt(pow(mOffsetFromPlayer.x, 2) + pow(mOffsetFromPlayer.y, 2)));
		mPosition.x = playerPosition->x + (mOffsetFromPlayer.x * reticleNormalizationFactor * MAX_RETICLE_OFFSET);
		mPosition.y = playerPosition->y + (mOffsetFromPlayer.y * reticleNormalizationFactor * MAX_RETICLE_OFFSET);
		if (!mVibrated && mTimeVibrated < VIBRATE_TIME)
		{
			vibration->wLeftMotorSpeed = RETICLE_VIBRATION_VALUE;
		}
		mVibrated = true;
	}
	else
	{
		mVibrated = false;
		mTimeVibrated = 0;
	}
	//XInputSetState(mID, vibration);

	if (mPosition.x >= (float)CGame::mViewingVolumeXMax)
	{
		mPosition.x = CGame::mViewingVolumeXMax;
	}
	else if (mPosition.x <= (float)CGame::mViewingVolumeXMin)
	{
		mPosition.x = CGame::mViewingVolumeXMin;
	}

	if (mPosition.y >= (float)CGame::mViewingVolumeYMax)
	{
		mPosition.y = CGame::mViewingVolumeYMax;
	}
	else if (mPosition.y <= (float)CGame::mViewingVolumeYMin)
	{
		mPosition.y = CGame::mViewingVolumeYMin;
	}

}

Coord2D ReticleC::ReturnPosition()
{
	return mPosition;
}

void ReticleC::render()
{
	RenderSprites({ mPosition.x - offsetBGFromCenter.x, mPosition.y - offsetBGFromCenter.y }, { BG_SIZE_X, BG_SIZE_Y }, mBGTexID, 0, 0, 1, 1, false);
	RenderSprites({mPosition.x - offsetFromCenter.x, mPosition.y - offsetFromCenter.y}, mSize, mTexID, 0, 0, 1, 1, false, mRenderColor);
}