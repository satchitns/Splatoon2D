#include <windows.h>											// Header File For Windows
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "openglframework.h"														// Header File For The NeHeGL Basecode
#include "baseTypes.h"
#include "collInfo.h"
#include "Object.h"
#include "Utils.h"
#include "Player.h"
#include "InputManager.h"
#include "game.h"
#include "Background.h"
#include <stdio.h>
#include <Xinput.h>

#define JOYSTICK_RANGE 32768
#define JOYSTICK_MIN_R_VALUE 5000
#define JOYSTICK_MIN_L_VALUE 25000
#define TRIGGER_MIN_VALUE 0

InputManagerC* InputManagerC::sInstance = NULL;

InputManagerC *InputManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new InputManagerC();
	return sInstance;
}

void InputManagerC::update(DWORD milliseconds)
{
	DWORD dwResult;

	XINPUT_STATE state[MAX_PLAYER_COUNT];

	for (DWORD i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		ZeroMemory(&state[i], sizeof(XINPUT_STATE));

		//get the state of the controller from XInput
		dwResult = XInputGetState(i, &state[i]);

		if (dwResult == ERROR_SUCCESS)
		{
			//Controller is connected

			if (!CGame::GetInstance()->mGameOver)
			{
				if (!CGame::GetInstance()->mIsInMainMenu)
				{
					if (abs(state[i].Gamepad.sThumbLX) > JOYSTICK_MIN_L_VALUE || abs(state[i].Gamepad.sThumbLY) > JOYSTICK_MIN_L_VALUE)
					{
						PlayerC::GetInstanceByID(i)->move(milliseconds, ((float)state[i].Gamepad.sThumbLX / JOYSTICK_RANGE), ((float)state[i].Gamepad.sThumbLY / JOYSTICK_RANGE));
					}

					if (abs(state[i].Gamepad.sThumbRX) > JOYSTICK_MIN_R_VALUE || abs(state[i].Gamepad.sThumbRY) > JOYSTICK_MIN_R_VALUE)
					{
						PlayerC::GetInstanceByID(i)->updateSpriteAnimStateAndReticleOffset(milliseconds, ((float)state[i].Gamepad.sThumbRX / JOYSTICK_RANGE), ((float)state[i].Gamepad.sThumbRY / JOYSTICK_RANGE));
					}

					if (state[i].Gamepad.bRightTrigger > TRIGGER_MIN_VALUE)
					{
						PlayerC* player = PlayerC::GetInstanceByID(i);
						if (player != NULL)
						{
							player->paint();
						}
						//call painting functionality
					}

					if (state[i].Gamepad.bLeftTrigger > TRIGGER_MIN_VALUE)
					{
						PlayerC* player = PlayerC::GetInstanceByID(i);
						if (player != NULL)
						{
							player->SetSquidState();
						}
						//call painting functionality
					}
					else
					{
						PlayerC* player = PlayerC::GetInstanceByID(i);
						if (player != NULL)
						{
							player->ClearSquidState();
						}
					}


					if (state[i].Gamepad.wButtons & 0x0010)
					{
						//implement restart functionality
						CGame::GetInstance()->mIsInMainMenu = true;
						CGame::GetInstance()->shutdown();
						CGame::CreateInstance()->init();
					}
				}
				else
				{
					if (state[i].Gamepad.wButtons & 0x1000)
					{
						CGame::GetInstance()->mIsInMainMenu = false;
						CGame::GetInstance()->init();
					}

					if (state[i].Gamepad.wButtons & 0x2000)
					{
						//quit game
						exit(0);
					}
				}
			}
			else
			{
				if (state[i].Gamepad.wButtons & 0x2000)
				{
					CGame::GetInstance()->mIsInMainMenu = true;
					CGame::GetInstance()->shutdown();
					CGame::CreateInstance()->init();
					BackgroundC::getInstance()->drawMainMenu();
				}
			}

		}

	}

}