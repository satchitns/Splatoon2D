#include <windows.h>											// Header File For Windows
#include "baseTypes.h"
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include <math.h>
//#include <stdlib.h>
#include <stdio.h>

const float DEG2RAD = 3.14159f/180.0f;


void DrawCircle(float_t radius, float_t x, float_t y, char8_t r, char8_t g, char8_t b, bool filled)
{
	
	glEnable(GL_POINT_SMOOTH);
	if(!filled)
	{
		glDisable(GL_TEXTURE_2D);
		glColor4ub(r, g, b,0xFF);
		// Set the point size
		glPointSize(1.0);
		glBegin(GL_POINTS);
		float_t radiusMax = radius + 2.0f;
		float_t radiusMin = radius - 2.0f;
		for (int i=0; i < 360; i+=2)
		{
			float degInRad = i*DEG2RAD;
			glVertex2f(x + (cos(degInRad)*radius),y + (sin(degInRad)*radius));
			glVertex2f(x + (cos(degInRad)*radiusMax),y + (sin(degInRad)*radiusMax));
			glVertex2f(x + (cos(degInRad)*radiusMin),y + (sin(degInRad)*radiusMin));
		}
		glEnd();
	}
	else
	{
	    glColor4ub(r, g, b,0xFF);
		glEnable(GL_BLEND); 
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		glPointSize(radius/2.0f);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}
}

void DrawLine(float_t startX, float_t startY, float_t endX, float_t endY, char8_t r, char8_t g, char8_t b)
{
	glColor3ub(r, g, b);
	// Draw filtered lines
	glEnable(GL_LINE_SMOOTH);

	glBegin(GL_LINE_STRIP);
		glVertex2f(startX, startY);
		glVertex2f(endX, endY);
	glEnd();

}
