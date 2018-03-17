#include <windows.h>											// Header File For Windows

#include <gl\gl.h>											// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"

#include "SOIL.h"
#include "baseTypes.h"
#include "game.h"
#include<math.h>
#include "PaintingBG.h"
#include "Collinfo.h"
#include "Object.h"
#include "MapElement.h"


BackgroundC* BackgroundC::sInstance = NULL;
MapElement* mapElementArray[200000];
int index = 0;
BackgroundC::BackgroundC()
{
	

}

void BackgroundC::init()
{
	mTexID = SOIL_load_OGL_texture("Sprites/Background_1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	mMapID = SOIL_load_OGL_texture("Sprites/Paint.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	for (int i = 0; i < 96; i++)
	{

			mapElementArray[i] = NULL;

	}

}

BackgroundC::~BackgroundC()
{

}

void BackgroundC::render()
{
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, mTexID);

	if (decalPaintedInFrame)
	{
		MapElement *element = new MapElement();

		mapElementArray[index++] = element;
		element->init(decalPosition);
		//glTexSubImage2D(GL_TEXTURE_2D, 0, decalPosition.x, decalPosition.y, DECAL_WIDTH, DECAL_HEIGHT, GL_RGBA, GL_UNSIGNED_INT, pixel_byte);
		decalPaintedInFrame = false;
	}

	glBegin(GL_QUADS);
	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

	glTexCoord2f(0, 0);
	glVertex3f(-960, -504, 0);

	glTexCoord2f(1, 0);
	glVertex3f(960, -504, 0);

	glTexCoord2f(1, 1);
	glVertex3f(960, 504, 0);

	glTexCoord2f(0, 1);
	glVertex3f(-960, 504, 0);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, mMapID);
	glBegin(GL_QUADS);	
	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	for (int i = 0; i < index; i++)
	{
		mapElementArray[i]->render();
	}
	glEnd();
}

void BackgroundC::sprayPaint(Coord2D position)
{
	decalPaintedInFrame = true;
	decalPosition = position;
	//position.x -= (float)DECAL_WIDTH / 2;
	//position.y += (float)DECAL_HEIGHT / 2;

}

BackgroundC* BackgroundC::CreateInstance()
{
	if (sInstance != NULL)return sInstance;
	else

		sInstance = new BackgroundC();
	return sInstance;
}