#pragma once
#include "MapElement.h"

#define DECAL_WIDTH 32
#define DECAL_HEIGHT 32

#define COL_1 5
#define COL_2 3
#define COL_3 1

#define MAP_ROWS ((CGame::mViewingVolumeXMax - CGame::mViewingVolumeXMin) / TILE_SIZE)
#define MAP_COLUMNS ((CGame::mViewingVolumeYMax - CGame::mViewingVolumeYMin) / TILE_SIZE)

#define CIRCLE_RADIUS 5
#define DEATH_RADIUS_MODIFIER 3.0f
#define PADDING (CIRCLE_RADIUS * 15)
#define HALF_PADDING PADDING/2

#define MAP_ACTUAL_ROWS MAP_ROWS + PADDING
#define MAP_ACTUAL_COLUMNS MAP_COLUMNS + PADDING

#define BACKGROUND_SPRITE "Sprites/DiaryBackground.png"
#define MAIN_MENU_SPRITE "Sprites/MainMenuScreen.png"

#define PERCENT_MOD	100
#define PERCENT_CAP	50
#define EDGE_PERCENT_MOD 10
#define EDGE_PERCENT_CAP 4

class BackgroundC
{
public:
	BackgroundC();
	~BackgroundC();
	static BackgroundC* createInstance();
	static BackgroundC*	getInstance() { return sInstance; };

	void render();
	void init();
	void update();
	void updateScore();
	void drawMainMenu();
	void handleGameOver();
	float getPlayerScore(int playerID);
	void sprayPaint(Coord2D position, ColorT color, int playerID, float radiusModifier, bool isDeathPaint = false);
	ColorT returnColorAtPoint(Coord2D point);


private:
	void drawCircleAtPosition(int x, int y, int playerID);
	void drawDeathPaint(int x, int y, int playerID);

	static MapElement mMapArray[MAP_ROWS + PADDING][MAP_COLUMNS + PADDING];
	static BackgroundC* sInstance;

	ColorT mPlayerPaintColor[MAX_PLAYER_COUNT];
	Coord2D mPlayerPaintPosition[MAX_PLAYER_COUNT];

	float mPlayerRadiusModifier[MAX_PLAYER_COUNT];

	GLuint mTexID;
	GLuint mMapID;
	GLuint mWinScreens[MAX_PLAYER_COUNT];
	
	int mScore[MAX_PLAYER_COUNT];

	bool mPlayerPaintedInFrame[MAX_PLAYER_COUNT];
	bool mDeathPaintArray[MAX_PLAYER_COUNT];
};

