#define FIELD_MANAGER_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collinfo.h"
#include "object.h"
#include "field.h"
#include "FieldManager.h"

FieldManagerC* FieldManagerC::sInstance=NULL;


FieldManagerC *FieldManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new FieldManagerC();
	return sInstance;
}
void FieldManagerC::init()
{
	mFieldPtr = new FieldC(0.0f,0.0f,3500,3500,0x00FF0000);
}
FieldC *FieldManagerC::getFieldPtr()
{
	return mFieldPtr;
}
void FieldManagerC::renderField()
{
	mFieldPtr->render();
}
void FieldManagerC::shutdown()
{
	delete mFieldPtr;
}