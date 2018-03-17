#define STATE_MANAGER_CPP
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
#include "stateManager.h"

StateManagerC* StateManagerC::sInstance=NULL;


StateManagerC *StateManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new StateManagerC();
	return sInstance;
}
int32_t StateManagerC::getState()
{
	return mCurrentState;
}
void StateManagerC::setState(int32_t state)
{
	mCurrentState = state;
}
void StateManagerC::shutdown()
{
}