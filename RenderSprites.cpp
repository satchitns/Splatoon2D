#include <windows.h>											// Header File For Windows

#include <gl\gl.h>											// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "SOIL.h"
#include "baseTypes.h"
#include "Utils.h"
#include "RenderSprites.h"


void RenderSprites(Coord2D position, Coord2D size, GLuint texID, float minU, float minV, float maxU, float maxV, bool bilinear, Color color)
{
	Coord2D minUV = { minU, minV };
	Coord2D maxUV = { maxU, maxV };
	RenderSprites(position, size, texID, minUV, maxUV, bilinear, color);
}
void RenderSprites(Coord2D position, Coord2D size, GLuint texID, Coord2D minUV, Coord2D maxUV, bool bilinear, Color color)
{
	glEnable(GL_TEXTURE_2D);
	if (!bilinear)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	glColor4ub(color.R, color.G, color.B, color.A);

	glTexCoord2f(minUV.x, minUV.y);
	glVertex3f(position.x, position.y, 0);

	glTexCoord2f(maxUV.x, minUV.y);
	glVertex3f(position.x + size.x, position.y, 0);

	glTexCoord2f(maxUV.x, maxUV.y);
	glVertex3f(position.x + size.x, position.y + size.y, 0);

	glTexCoord2f(minUV.x, maxUV.y);
	glVertex3f(position.x, position.y + size.y, 0);
	glEnd();
}
