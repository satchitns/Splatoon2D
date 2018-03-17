#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#include <gl\gl.h>											// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"

#include "Utils.h"
#include "game.h"
#include "RenderSprites.h"
#include "SOIL.h"

#include "Timer.h"

CTimer* CTimer::sInstance = nullptr;

CTimer* CTimer::createInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new CTimer();
	}
	return sInstance;
}

void CTimer::init(GLuint* numTexes)
{
	mTimeLeft = MATCH_TIME;
	mNumTexes = numTexes;
	mPosition.x = CGame::mViewingVolumeXMax - TIMER_POSITION_OFFSET_X;
	mPosition.y = CGame::mViewingVolumeYMax - TIMER_POSITION_OFFSET_Y;
	mMinutes = 0.0f;
	mSecondsUnits = 0;
	mSecondsTens = 0;
	mColonTexture = SOIL_load_OGL_texture(COLON_TEXTURE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS);
}

void CTimer::update(DWORD milliseconds)
{
	mTimeLeft -= (float) milliseconds / 1000;
	mMinutes = (int)((float)mTimeLeft / 60);
	mSecondsTens = (int)(((int)mTimeLeft % 60) / 10);
	mSecondsUnits = (int)(((int)mTimeLeft % 60) % 10);

	if (mTimeLeft <= 0.0f)
	{
		mMinutes = 0;
		mSecondsTens = 0;
		mSecondsUnits = 0;

		CGame::GetInstance()->mGameOver = true;

	}
}

void CTimer::render()
{
	RenderSprites({ mPosition.x + DIGIT_0_OFFSET, mPosition.y }, { TIMER_UI_WIDTH, TIMER_UI_HEIGHT }, mNumTexes[mSecondsUnits], { 0, 0 }, { 1, 1 }, false);
	RenderSprites({ mPosition.x + DIGIT_1_OFFSET, mPosition.y }, { TIMER_UI_WIDTH, TIMER_UI_HEIGHT }, mNumTexes[mSecondsTens], { 0, 0 }, { 1, 1 }, false);
	RenderSprites({ mPosition.x + COLON_OFFSET, mPosition.y }, { TIMER_UI_WIDTH, TIMER_UI_HEIGHT }, mColonTexture, { 0, 0 }, { 1, 1 }, false);
	RenderSprites({ mPosition.x + DIGIT_2_OFFSET, mPosition.y }, { TIMER_UI_WIDTH, TIMER_UI_HEIGHT }, mNumTexes[mMinutes], { 0, 0 }, { 1, 1 }, false);
}

void CTimer::shutdown()
{
	delete sInstance;
}