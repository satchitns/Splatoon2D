/*
Background.cpp - Handles the background rendering, including the painting in Splatoon 2D. Painting is tile-based, with the background being divided into a number of square cells of configurable size.
The cells exist as a static matrix, and when the player sends an instruction to paint at a particular point, the grid in which the paint instruction happened is calculated and the cell color is updated.  
The radius of the set of cells drawn on each paint call increases as the painting continues, giving each paint stretch the appearance of an actual paint stroke. The paint cells in the set are also drawn with a 
configurable probability, making the painting look more realistic. The smaller the cell size, the less boxy the painting looks. When a player dies, it calls a special paint function that draws a splatter that grows
over time every frame till max size. The whole matrix is drawn each frame in render.The score is also calculated in the background class every frame, and returned to the player when the player requests it (every frame). 
Background also paints the main menu and the win screens, depending on the state in Game. 
*/
#include <windows.h>										// Header File For Windows
#include <gl\gl.h>											// Header File For The OpenGL32 Library
#include <gl\glu.h>											// Header File For The GLu32 Library
#include "glut.h"

#include "SOIL.h"
#include "baseTypes.h"
#include "game.h"
#include<math.h>
#include "Collinfo.h"
#include "Object.h"
#include "Utils.h"
#include "MapElement.h"
#include "Player.h"
#include "random.h"
#include "Background.h"




BackgroundC* BackgroundC::sInstance = NULL;

MapElement BackgroundC::mMapArray[MAP_ROWS + PADDING][MAP_COLUMNS + PADDING];


BackgroundC::BackgroundC()
{

}

BackgroundC::~BackgroundC()
{

}


/*
Init : Performs initialization for the Background class. Loads in background textures, and win-screens. Initializes the background paint array to 
be of no color, and sets the world position of each cell in the grid. Initializes player score and other player related variables to their undefined/default values.
*/
void BackgroundC::init()
{
	srand(timeGetTime());

	if (CGame::GetInstance()->mIsInMainMenu)
	{
		drawMainMenu();
	}
	else
	{
		mTexID = SOIL_load_OGL_texture(BACKGROUND_SPRITE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			 SOIL_FLAG_INVERT_Y);
		mWinScreens[0] = SOIL_load_OGL_texture("Sprites/blue_wins.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			 SOIL_FLAG_INVERT_Y);

		mWinScreens[1] = SOIL_load_OGL_texture("Sprites/orange_wins.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);

		mWinScreens[2] = SOIL_load_OGL_texture("Sprites/green_wins.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y);

		mWinScreens[3] = SOIL_load_OGL_texture("Sprites/purple_wins.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);
	}

	for (int i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		mPlayerPaintedInFrame[i] = false;
		mPlayerPaintColor[i] = NONE;
		mScore[i] = 0.0f;
	}

	for (int i = 0; i < MAP_ACTUAL_ROWS; i++)
	{
		for (int j = 0; j < MAP_ACTUAL_COLUMNS; j++)
		{
			float xPosition = (i - HALF_PADDING) * TILE_SIZE - CGame::mViewingVolumeXMax;
			float yPosition = (j - HALF_PADDING) * TILE_SIZE - CGame::mViewingVolumeYMax;
			mMapArray[i][j].init({ xPosition, yPosition });
		}
	}
	for (int i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		mDeathPaintArray[i] = false;
	}

}

/*
DrawMainMenu : Sets the texture ID to be bound to the main menu, and calls the render function.
*/
void BackgroundC::drawMainMenu()
{
	mTexID = SOIL_load_OGL_texture(MAIN_MENU_SPRITE, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	render();
}

/*
GetPlayerScore : Returns the score of the player whose ID was passed.
Input :	player ID (integer)
Output : player score (float)
*/
float BackgroundC::getPlayerScore(int playerID)
{
	float playerScore = 0.0f;
	float totalOccupied = 0.01f;
	for (int i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		totalOccupied += mScore[i];
	}
	playerScore = ((float)mScore[playerID] / totalOccupied) * 100.5f;

	return playerScore;
}

/*
Update : Calls update score, which updates the score for each player.
*/
void BackgroundC::update()
{
	updateScore();
}

/*
HandleGameOver : Calculates the maximum score to find the winner, changes the texture ID to the ID of the winner's win screen, and calls render.
*/
void BackgroundC::handleGameOver()
{
	//handle tie case
	int maxScore = -1;
	int maxPlayer = 0;
	updateScore();
	for (int i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		if (mScore[i] > maxScore)
		{
			maxScore = mScore[i];
			maxPlayer = i;
		}
	}

	mTexID = mWinScreens[maxPlayer];


	render();
}

/*
UpdateScore : Updates the score of each player using the following formula : 
			  Player Score = (Occupied tiles of player color)/(Total number of occupied tiles)	
*/
void BackgroundC::updateScore()
{
	for (int i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		mScore[i] = 0;
	}
	for (int i = 0; i < MAP_ACTUAL_ROWS; i++)
	{
		for (int j = 0; j < MAP_ACTUAL_COLUMNS; j++)
		{
			for (int k = 0; k < MAX_PLAYER_COUNT; k++)
			{
				if (mMapArray[i][j].myColor == PlayerC::GetInstanceByID(k)->getColor())
				{
					mScore[k] += 1;
				}
			}
		}
	}
}

/*
Render : Renders a white backdrop first, then the actual background. Converts the location the player sent in the last frame to grid co-ordinates, 
and changes a set of cells around that cell to that player's color. If the player was dead, it changes the cells in a larger radius.
Renders the paint cells if the game isn't over. The paint cells are rendered as quads without textures.
*/
void BackgroundC::render()
{

	/*Backdrop*/
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

	glVertex3f(-CGame::mViewingVolumeXMax, -CGame::mViewingVolumeYMax, 0);

	glVertex3f(CGame::mViewingVolumeXMax, -CGame::mViewingVolumeYMax, 0);

	glVertex3f(CGame::mViewingVolumeXMax, CGame::mViewingVolumeYMax, 0);

	glVertex3f(-CGame::mViewingVolumeXMax, CGame::mViewingVolumeYMax, 0);

	glEnd();

	/*Background with alpha*/
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, mTexID);
	glBegin(GL_QUADS);
	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

	glTexCoord2f(0, 0);
	glVertex3f(-CGame::mViewingVolumeXMax, -CGame::mViewingVolumeYMax, 0);

	glTexCoord2f(1, 0);
	glVertex3f(CGame::mViewingVolumeXMax, -CGame::mViewingVolumeYMax, 0);

	glTexCoord2f(1, 1);
	glVertex3f(CGame::mViewingVolumeXMax, CGame::mViewingVolumeYMax, 0);

	glTexCoord2f(0, 1);
	glVertex3f(-CGame::mViewingVolumeXMax, CGame::mViewingVolumeYMax, 0);
	glEnd();

	/*Figuring out player painted cells in the last frame, and filling in cells in the matrix to be drawn later*/
	for (int playerID = 0; playerID < MAX_PLAYER_COUNT; playerID++)
	{
		if (mPlayerPaintedInFrame[playerID])
		{

			mPlayerPaintPosition[playerID].x = floor(mPlayerPaintPosition[playerID].x / TILE_SIZE);
			mPlayerPaintPosition[playerID].y = floor(mPlayerPaintPosition[playerID].y / TILE_SIZE);

			mPlayerPaintPosition[playerID].x += (CGame::mViewingVolumeXMax/TILE_SIZE) + HALF_PADDING;
			mPlayerPaintPosition[playerID].y += (CGame::mViewingVolumeYMax / TILE_SIZE) + HALF_PADDING;

			if (mDeathPaintArray[playerID])
			{
				drawDeathPaint(mPlayerPaintPosition[playerID].x, mPlayerPaintPosition[playerID].y, playerID);
				mDeathPaintArray[playerID] = false;
			}
			else
			{
				drawCircleAtPosition(mPlayerPaintPosition[playerID].x, mPlayerPaintPosition[playerID].y, playerID);
			}
			mPlayerPaintedInFrame[playerID] = false;
		}
	}

	/*Drawing the paint matrix*/
	if (!CGame::GetInstance()->mGameOver)
	{
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		for (int i = 0; i < MAP_ACTUAL_ROWS; i++)
		{
			for (int j = 0; j < MAP_ACTUAL_COLUMNS; j++) {
				if (mMapArray[i][j].myColor != NONE)
				{
					mMapArray[i][j].render();
				}
			}
		}
		glEnd();
	}


}

/*
DrawCircleAtPosition : Converts a set of cells in the array around the given X and Y,
to the color of the player specified by the player ID. Leaves some random cells unfilled for stylistic effect.
Input : Position as x and y, player ID
Output : -
*/
void BackgroundC::drawCircleAtPosition(int x, int y, int playerID)
{
	int xMax = x + (CIRCLE_RADIUS * mPlayerRadiusModifier[playerID]);
	int xMin = x - (CIRCLE_RADIUS * mPlayerRadiusModifier[playerID]);
	int yMax = y + (CIRCLE_RADIUS * mPlayerRadiusModifier[playerID]);
	int yMin = y - (CIRCLE_RADIUS * mPlayerRadiusModifier[playerID]);

	for (int i = xMin; i < xMax; i++)
	{
		for (int j = yMin; j < yMax; j++)
		{
			if ((i == (xMin) || i == (xMax)) && (j == (yMin) || j == (yMax))) //border cell (higher probability to be empty)

			{
				if (rand() % EDGE_PERCENT_MOD < EDGE_PERCENT_CAP)
				{
					mMapArray[i][j].myColor = mPlayerPaintColor[playerID];
				}
			}
			else
			{
				if (rand() % PERCENT_MOD < PERCENT_CAP)
				{
					mMapArray[i][j].myColor = mPlayerPaintColor[playerID];
				}

			}
		}
	}
}

/*
DrawDeathPaint : Converts a set of cells in the array around the given X and Y,
to the color of the player specified by the player ID, in a larger radius than normal. 
Leaves some random cells unfilled for stylistic effect.
Input : Position as x and y, player ID
Output : -
*/
void BackgroundC::drawDeathPaint(int x, int y, int playerID)
{
	int deathCircleRadius = CIRCLE_RADIUS * mPlayerRadiusModifier[playerID];
	for (int i = x - deathCircleRadius; i < x + deathCircleRadius; i++)
	{
		for (int j = y - deathCircleRadius; j < y + deathCircleRadius; j++)
		{
			if ((i == (x - deathCircleRadius) || i == (x + deathCircleRadius)) && ( j == (y - deathCircleRadius) || j == (y + deathCircleRadius) )) //border cells
			
			{
				if (rand() % EDGE_PERCENT_MOD < EDGE_PERCENT_CAP)
				{
					mMapArray[i][j].myColor = mPlayerPaintColor[playerID];
				}
			}
			else
			{
				if (rand() % PERCENT_MOD < PERCENT_CAP)
				{
					mMapArray[i][j].myColor = mPlayerPaintColor[playerID];
				}

			}
		}
	}
}

/*
SprayPaint : Sets a set of variables that indicate player paint information in the current frame. This information is used
			 in the render function to actually create the paint circles in the paint array, and print them.
Input : Position of player's paint modifications, player's color, player's ID, current size of paint circle, and whether the player is dead
Output : - 
*/
void BackgroundC::sprayPaint(Coord2D position, ColorT color, int playerID, float radiusModifier, bool isDeathPaint)
{
	mPlayerPaintedInFrame[playerID] = true;
	mDeathPaintArray[playerID] = isDeathPaint;
	mPlayerPaintPosition[playerID] = position;
	mPlayerPaintColor[playerID] = color;
	mPlayerRadiusModifier[playerID] = radiusModifier;
}


/*
ReturnColorAtPoint : Returns the color at a given screen point.
Input : Point at which the color is to be polled
Output : The color at the point
*/
ColorT BackgroundC::returnColorAtPoint(Coord2D point)
{

	point.x = floor(point.x / TILE_SIZE);
	point.y = floor(point.y / TILE_SIZE);

	point.x += (CGame::mViewingVolumeXMax / TILE_SIZE) + HALF_PADDING;
	point.y += (CGame::mViewingVolumeYMax / TILE_SIZE) + HALF_PADDING;
	return mMapArray[(int)point.x][(int)point.y].myColor;
}

/*
CreateInstance : Creates an instance of background if it doesn't already exist, assigns it to the static
				 background pointer and returns it.
Input : -
Output : Pointer to the instance
*/
BackgroundC* BackgroundC::createInstance()
{
	if (sInstance != NULL)return sInstance;
	else

		sInstance = new BackgroundC();
	return sInstance;
}