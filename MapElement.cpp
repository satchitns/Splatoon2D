#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#include <gl\gl.h>											// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"



#include "collInfo.h"
#include "baseTypes.h"
#include "Object.h"
#include "Utils.h"
#include "UI.h"
#include "RenderSprites.h"
#include "MapElement.h"




MapElement::MapElement()
{
}

void MapElement::init(Coord2D position)
{
	mPosition = position;

	myColor = NONE;
}

MapElement::~MapElement()
{
}

void MapElement::render()
{
	Color color = ReturnColorFromEnum(myColor);
	glColor4ub(color.R, color.G, color.B, 255/*color.A*/);

	glVertex3f(mPosition.x, mPosition.y, 0);


	glVertex3f(mPosition.x + TILE_SIZE, mPosition.y, 0);


	glVertex3f(mPosition.x + TILE_SIZE, mPosition.y + TILE_SIZE, 0);

	glVertex3f(mPosition.x, mPosition.y + TILE_SIZE, 0);
}
