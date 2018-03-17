#pragma once
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#include <gl\gl.h>											// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"


#include "collInfo.h"

#include "Object.h"
#include "Utils.h"
#include "game.h"
#include "RenderSprites.h"
#include "SOIL.h"
#include "UI.h"



UI::UI()
{
}


UI::~UI()
{
}

void UI::init(GLuint BGTexID, GLuint FillTexID, Coord2D offset, UIType type, Color color)
{
	mUIType = type;
	mBGTexID = BGTexID;
	mSize = { UI_WIDTH, UI_HEIGHT };
	mFillTexID = FillTexID;
	mOffset = { 0, 0 };
	switch (mUIType)
	{
	case HP:
		mColor = { 255, 0, 0, 255 };
		break;
	case PAINT:
		mColor = color;
		break;
	default:
		break;
	}
}

void UI::render()
{
	RenderSprites({ mPosition.x - mOffset.x , mPosition.y - mOffset.y }, mSize, mBGTexID, { 0, 0 }, { 1, 1 }, false);
	RenderSprites({ mPosition.x - mOffset.x , mPosition.y - mOffset.y }, {mSize.x * mAmount, mSize.y}, mFillTexID, { 0, 0 }, { 1, 1 }, false, mColor);
}

void UI::update(Coord2D position, float amount)
{
	mPosition = position;
	mAmount = amount;
}

Color ReturnColorFromEnum(ColorT color)
{
	switch (color)
	{
	case GREEN:
		return { 0x8C, 0xF2, 0x19, 0xFF };
	case PINK:
		return { 0xBE, 0x13, 0xF8, 0xFF };
	case BLUE:
		return { 0x3F, 0x48, 0xCC, 0xFF };
	case ORANGE:
		return { 0xFF, 0x82, 0x0C, 0xFF };
	default: case NONE:
		return { 255, 255, 255, 255 };
	}
}