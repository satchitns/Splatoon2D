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

#include "ScoreUI.h"

void ScoreUI::init(GLuint *numTexes, bool isRespawnUI)
{
	mIsRespawnUI = isRespawnUI;
	unitsScore = tensScore = hundredsScore = 0;
	mNumTexes = numTexes;
}

void ScoreUI::render()
{
	if (!mIsRespawnUI)
	{
		RenderSprites({ mPosition.x + DIGIT_0_OFFSET, mPosition.y }, { SCORE_UI_WIDTH, SCORE_UI_HEIGHT }, mNumTexes[unitsScore], { 0,0 }, { 1,1 }, false);
		RenderSprites({ mPosition.x + DIGIT_1_OFFSET, mPosition.y }, { SCORE_UI_WIDTH, SCORE_UI_HEIGHT }, mNumTexes[tensScore], { 0,0 }, { 1,1 }, false);
		RenderSprites({ mPosition.x + DIGIT_2_OFFSET, mPosition.y }, { SCORE_UI_WIDTH, SCORE_UI_HEIGHT }, mNumTexes[hundredsScore], { 0,0 }, { 1,1 }, false);
	}
	else 
	{
		RenderSprites({ mPosition.x , mPosition.y }, { RESPAWN_UI_WIDTH, RESPAWN_UI_HEIGHT }, mNumTexes[unitsScore], { 0,0 }, { 1,1 }, false);
	}
}

void ScoreUI::update(float score, Coord2D position)
{
	mPosition = position;
	unitsScore = (int)score % 10;
	tensScore = ((int)score % 100)/10;
	hundredsScore = (int)score / 100;
}

ScoreUI::ScoreUI()
{
}


ScoreUI::~ScoreUI()
{
}
