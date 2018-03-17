#define GAME_CPP
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
#include "collInfo.h"
#include "object.h"
#include "ball.h"
#include "field.h"
#include "player.h"
#include "random.h"
#include "gameObjects.h"
#include "openGLStuff.h"
#include "game.h"
#include "StateManager.h"
#include "BallManager.h"
#include "FieldManager.h"
#include "InputManager.h"
#include "SpriteDemoManager.h"
#include "Background.h"
#include "SOIL.h"
#include "AudioManager.h"

#include "Timer.h"

// Declarations
const char8_t CGame::mGameTitle[]="Splatoon2D";

CGame* CGame::sInstance=NULL;
GLuint digitTexture[10];
#define FILE_NAME_SIZE 20
BOOL Initialize (GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	CGame::CreateInstance();
	CGame::GetInstance()->mIsInMainMenu = true;
	BackgroundC::createInstance()->init();
	InputManagerC::CreateInstance();
	InputManagerC::GetInstance()->init();
	initOpenGLDrawing(window,keys,0.0f, 0.0f, 0.0f);
	CGame::GetInstance()->init();
	return TRUE;						
}

void CGame::init()
{
	mGameOver = false;
	if (!CGame::GetInstance()->mIsInMainMenu)
	{
		BackgroundC::getInstance()->init();
		AudioManager::createInstance()->init();
		GLuint playerTexture = SOIL_load_OGL_texture(SPRITE_PATH, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			 SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS);
		GLuint reticleTexture = SOIL_load_OGL_texture("Sprites/Reticle.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS);
		GLuint reticleBGTexture = SOIL_load_OGL_texture("Sprites/ReticleBG.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			 SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS);
		GLuint bgTexture = SOIL_load_OGL_texture("Sprites/UI_Outline.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			 SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS);
		GLuint fillTexture = SOIL_load_OGL_texture("Sprites/UI_Fill.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS);

		char textureName[FILE_NAME_SIZE];
		for (int i = 0; i < 10; i++)
		{
			sprintf(textureName, "Sprites/%d.png", i);
			digitTexture[i] = SOIL_load_OGL_texture(textureName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS);
		}

		InputManagerC::CreateInstance();
		//BackgroundC::GetInstance()->init();
		for (int i = 0; i < MAX_PLAYER_COUNT; i++)
			PlayerC::CreateInstanceByID(i)->init(i, playerTexture, reticleTexture, reticleBGTexture, bgTexture, fillTexture, digitTexture);
		InputManagerC::GetInstance()->init();

		CTimer::createInstance();
		CTimer::getInstance()->init(digitTexture);

		AudioManager::getInstance()->playSound(AudioManager::getInstance()->GetBackgroundMusic(), true);
	}
	else
	{
		BackgroundC::getInstance()->init();
	}
}
void CGame::UpdateFrame(DWORD milliseconds)			
{
	keyProcess();
	InputManagerC::GetInstance()->update(milliseconds);
	if (!CGame::GetInstance()->mIsInMainMenu)
	{
		for (int i = 0; i < MAX_PLAYER_COUNT; i++)
			PlayerC::GetInstanceByID(i)->update(milliseconds);
		BackgroundC::getInstance()->update();

		CTimer::getInstance()->update(milliseconds);
	}
	if (CGame::GetInstance()->mGameOver)
	{
		BackgroundC::getInstance()->handleGameOver();
	}
}

void CGame::DrawScene(void)											
{

	startOpenGLDrawing();
	BackgroundC::getInstance()->render();
	if (!GetInstance()->mGameOver)
	{
		if (!CGame::GetInstance()->mIsInMainMenu)
		{
			for (int i = 0; i < MAX_PLAYER_COUNT; i++)
			{
				PlayerC::GetInstanceByID(i)->render();
			}
			for (int i = 0; i < MAX_PLAYER_COUNT; i++)
			{
				PlayerC::GetInstanceByID(i)->reticleRender();
			}
			CTimer::getInstance()->render();
		}
	}
}


CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}
void CGame::shutdown()
{
	/*BallManagerC::GetInstance()->shutdown();
	StateManagerC::GetInstance()->shutdown();
	FieldManagerC::GetInstance()->shutdown();
	SpriteDemoManagerC::GetInstance()->shutdown();*/
	AudioManager::getInstance()->shutdown();
}
void CGame::DestroyGame(void)
{
	for (int i = 0; i < MAX_PLAYER_COUNT; i++)
		delete PlayerC::GetInstanceByID(i);
}