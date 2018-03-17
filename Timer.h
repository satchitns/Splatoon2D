#pragma once

#include <Windows.h>

#define MATCH_TIME 180.0f

#define TIMER_POSITION_OFFSET_X 640
#define TIMER_POSITION_OFFSET_Y 50

#define TIMER_UI_WIDTH 48
#define TIMER_UI_HEIGHT 36
#define DIGIT_2_OFFSET 0
#define COLON_OFFSET (TIMER_UI_WIDTH * 0.75f)
#define DIGIT_1_OFFSET ((TIMER_UI_WIDTH * 1.5f))
#define DIGIT_0_OFFSET ((TIMER_UI_WIDTH * 2.25f))

#define COLON_TEXTURE "Sprites/colon.png"

class CTimer
{
public:
	static CTimer* createInstance();
	static CTimer* getInstance() { return sInstance; }

	void init(GLuint* numTexes);
	void update(DWORD milliseconds);
	void render();

	void shutdown();

	float GetTimeLeft() { return mTimeLeft; }

private:
	static CTimer* sInstance;

	GLuint *mNumTexes;
	Coord2D mPosition;
	float mTimeLeft;
	GLuint mColonTexture;

	int mSecondsUnits;
	int mSecondsTens;
	int mMinutes;

};