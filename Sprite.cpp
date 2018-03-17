#include "Sprite.h"
#include "baseTypes.h"
#include "SOIL.h"
#include "glut.h"
#include "ShapeDraw.h"
#include "Collider.h"

#include <math.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <windows.h>

#define PI 3.14159265

Sprite::Sprite(float_t xPosition, float_t yPosition, uint16_t width, uint16_t height, char8_t* spriteName, uint8_t spriteLayer)
{

	setPosition(xPosition, yPosition);
	mWidth = width;
	mHeight = height;
	mSpriteTextureID = SOIL_load_OGL_texture(spriteName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

}

void Sprite::init()
{
	mRotation = 0;
	setVelocity(0, 0);
	enableSprite();
	mCollider = nullptr;
	//disableSprite();
}

void Sprite::render()
{
	// Return if sprite is disabled
	if (!getSpriteEnabled())	return;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mSpriteTextureID);
	
	glPushMatrix();

	glTranslatef(getPosition()->x, getPosition()->y, 0.0f);
	glRotatef(mRotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-getPosition()->x, -getPosition()->y, 0.0f);

	
	// Initiate drawing
	glBegin(GL_QUADS);
	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	// Top Left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(getPosition()->x, getPosition()->y + mHeight, mSpriteLayer);
	// Bottom Left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(getPosition()->x, getPosition()->y, mSpriteLayer);
	// Bottom Right
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(getPosition()->x + mWidth, getPosition()->y, mSpriteLayer);
	// Top Right
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(getPosition()->x + mWidth, getPosition()->y + mHeight, mSpriteLayer);
	//End Drawing
	glEnd();

	glPopMatrix();
}

void Sprite::updateSprite(DWORD milliseconds)
{

	if (!getSpriteEnabled())	return;


	// Update position
	float_t changeInX, changeInY;
	changeInX = getVelocity()->x * milliseconds / 1000.0f;
	changeInY = getVelocity()->y * milliseconds / 1000.0f;
	setPosition(getPosition()->x + changeInX, getPosition()->y + changeInY);
}

void Sprite::setRotation(float_t rotation)
{
	mRotation = rotation;
}

float_t Sprite::getRotation()
{
	return mRotation;
}

void Sprite::createCollider(int32_t x, int32_t y, int32_t width, int32_t height, ColliderTag tag, Sprite* sprite)
{
	mCollider = new Collider(x, y, width, height, tag, sprite);
}