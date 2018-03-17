#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "collInfo.h"
#include "object.h"
#include "field.h"
#include "ShapeDraw.h"


void FieldC::moveUp()
{
	int y;
	y=5;
}
FieldC::FieldC(float_t x, float_t y, uint32_t height, uint32_t width, uint32_t initColor)
{
    mEnabled = true;
    mFieldColor = initColor;
	mWidth = width;
	mHeight = height;
	mPosition.x = x;
	mPosition.y = y;
};
FieldC::~FieldC()
{
};
void FieldC::update(DWORD milliseconds)
{
};

void FieldC::render()
{
	float_t left = mPosition.x - (float_t)mWidth/2.0f;
	float_t right = mPosition.x + (float_t)mWidth/2.0f;
	float_t bottom = mPosition.y - (float_t)mHeight/2.0f;
	float_t top = mPosition.y + (float_t)mHeight/2.0f;

	char8_t r = (char8_t)(mFieldColor>>16 & 0xFF);
	char8_t g = (char8_t)(mFieldColor>>8 & 0xFF);
	char8_t b = (char8_t)(mFieldColor>>0 & 0xFF);

	DrawLine(left,top,right,top,r,g,b);
	DrawLine(right,top,right,bottom,r,g,b);
	DrawLine(right,bottom,left,bottom,r,g,b);
	DrawLine(left,bottom,left,top,r,g,b);
};
