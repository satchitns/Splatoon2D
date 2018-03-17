#include "PlaneManager.h"
#include "baseTypes.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Utility.h"
#include "game.h"
#include "GameManager.h"
#include "AudioManager.h"

#include <windows.h>
#include <assert.h>

PlaneManager* PlaneManager::sInstance = nullptr;

const float_t PlaneManager::minimumPlaneVelocity = 150.0f;
const float_t PlaneManager::maximumPlaneVelocity = 300.0f;
const float_t PlaneManager::timeForMaxingVelocity = 120.0f;


const int32_t PlaneManager::minimumAltitude1 = 578;
const int32_t PlaneManager::maximumAltitude1 = 700;

const int32_t PlaneManager::minimumAltitude2 = 400;
const int32_t PlaneManager::maximumAltitude2 = 522;

float_t PlaneManager::delayTimeBeforeLaunch = 4.0f;

PlaneManager* PlaneManager::createInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new PlaneManager();
	}
	return sInstance;
}

PlaneManager* PlaneManager::getInstance()
{
	return sInstance;
}

void PlaneManager::init()
{

	resetPositionRequiredA1 = FALSE;
	resetPositionRequiredA2 = FALSE;
	resetPositionRequiredB1 = FALSE;
	resetPositionRequiredB2 = FALSE;

	delayTimeForA1 = 0.0f;
	delayTimeForA2 = 0.0f;
	delayTimeForB1 = 0.0f;
	delayTimeForB2 = 0.0f;

	totalTime = 0.0f;

	currentBaseVelocity = minimumPlaneVelocity;

	lifeDecrementedA1 = TRUE;
	lifeDecrementedA2 = TRUE;
	lifeDecrementedB1 = TRUE;
	lifeDecrementedB2 = TRUE;
}

void PlaneManager::update(DWORD deltaTime)
{
	checkIfResetIsRequired();
	checkIfPlanesShouldBeLaunched(deltaTime);
	launchPlanes();
	timeBasedManipulation(deltaTime);
}

void PlaneManager::checkIfResetIsRequired()
{
	GameManager* gameManager = GameManager::getInstance();
	Sprite** spritePtrs = SpriteManager::getInstance()->getSpritePtrs();
	// Disable plane spawning if the game has ended
	
	if (gameManager->getGameEnd())
	{
		return;
	}
	
	if (spritePtrs[SpriteManager::SpriteName::PLANE_A_1]->getPosition()->x > CGame::mScreenWidth)
	{
		resetPositionRequiredA1 = TRUE;
		if (!lifeDecrementedA1)
		{
			gameManager->decrementLife('B');
			lifeDecrementedA1 = TRUE;
			AudioManager::getInstance()->playAirRaidSound();
		}
	}
	if (spritePtrs[SpriteManager::SpriteName::PLANE_A_2]->getPosition()->x > CGame::mScreenWidth)
	{
		resetPositionRequiredA2 = TRUE;
		if (!lifeDecrementedA2)
		{
			gameManager->decrementLife('B');
			lifeDecrementedA2 = TRUE;
			AudioManager::getInstance()->playAirRaidSound();
		}
	}
	if (spritePtrs[SpriteManager::SpriteName::PLANE_B_1]->getPosition()->x < -spritePtrs[SpriteManager::SpriteName::PLANE_B_1]->getWidth())
	{
		resetPositionRequiredB1 = TRUE;
		if (!lifeDecrementedB1)
		{
			gameManager->decrementLife('A');
			lifeDecrementedB1 = TRUE;
			AudioManager::getInstance()->playAirRaidSound();
		}
	}
	if (spritePtrs[SpriteManager::SpriteName::PLANE_B_2]->getPosition()->x < -spritePtrs[SpriteManager::SpriteName::PLANE_B_2]->getWidth())
	{
		resetPositionRequiredB2 = TRUE;
		if (!lifeDecrementedB2)
		{
			gameManager->decrementLife('A');
			lifeDecrementedB2 = TRUE;
			AudioManager::getInstance()->playAirRaidSound();
		}
	}
}

void PlaneManager::checkIfPlanesShouldBeLaunched(DWORD deltaTime)
{
	if (resetPositionRequiredB1)
	{
		delayTimeForB1 += deltaTime / 1000.0f;
		if (delayTimeForB1 > delayTimeBeforeLaunch)
		{
			delayTimeForB1 = 0.0f;
			resetPositionRequiredB1 = FALSE;
			launchPlaneB1 = TRUE;
		}
	}
	if (resetPositionRequiredB2)
	{
		delayTimeForB2 += deltaTime / 1000.0f;
		if (delayTimeForB2 > delayTimeBeforeLaunch)
		{
			delayTimeForB2 = 0.0f;
			resetPositionRequiredB2 = FALSE;
			launchPlaneB2 = TRUE;
		}
	}
	if (resetPositionRequiredA1)
	{
		delayTimeForA1 += deltaTime / 1000.0f;
		if (delayTimeForA1 > delayTimeBeforeLaunch)
		{
			delayTimeForA1 = 0.0f;
			resetPositionRequiredA1 = FALSE;
			launchPlaneA1 = TRUE;
		}
	}
	if (resetPositionRequiredA2)
	{
		delayTimeForA2 += deltaTime / 1000.0f;
		if (delayTimeForA2 > delayTimeBeforeLaunch)
		{
			delayTimeForA2 = 0.0f;
			resetPositionRequiredA2 = FALSE;
			launchPlaneA2 = TRUE;
		}
	}

}

void PlaneManager::launchPlanes()
{
	Sprite** spritePtrs = SpriteManager::getInstance()->getSpritePtrs();
	if(launchPlaneB1 && launchPlaneB2 && launchPlaneA1 && launchPlaneA2)
	{ 
		launchPlaneA1 = FALSE;
		launchPlaneA2 = FALSE;
		launchPlaneB1 = FALSE;
		launchPlaneB2 = FALSE;

		spritePtrs[SpriteManager::SpriteName::PLANE_B_1]->setVelocity(-Utility::getRandomNumber(currentBaseVelocity - 20.0f, currentBaseVelocity+20.0f), 0);
		spritePtrs[SpriteManager::SpriteName::PLANE_B_1]->setPosition(CGame::mScreenWidth, Utility::getRandomNumber(minimumAltitude1, maximumAltitude1));
		spritePtrs[SpriteManager::SpriteName::PLANE_B_1]->enableSprite();

		spritePtrs[SpriteManager::SpriteName::PLANE_B_2]->setVelocity(-Utility::getRandomNumber(currentBaseVelocity - 20.0f, currentBaseVelocity + 20.0f), 0);
		spritePtrs[SpriteManager::SpriteName::PLANE_B_2]->setPosition(CGame::mScreenWidth, Utility::getRandomNumber(minimumAltitude2, maximumAltitude2));
		spritePtrs[SpriteManager::SpriteName::PLANE_B_2]->enableSprite();

		spritePtrs[SpriteManager::SpriteName::PLANE_A_1]->setVelocity(Utility::getRandomNumber(currentBaseVelocity -20.0f, currentBaseVelocity + 20.0f), 0);
		spritePtrs[SpriteManager::SpriteName::PLANE_A_1]->setPosition(-100, Utility::getRandomNumber(minimumAltitude1, maximumAltitude1));
		spritePtrs[SpriteManager::SpriteName::PLANE_A_1]->enableSprite();

		spritePtrs[SpriteManager::SpriteName::PLANE_A_2]->setVelocity(Utility::getRandomNumber(currentBaseVelocity - 20.0f, currentBaseVelocity + 20.0f), 0);
		spritePtrs[SpriteManager::SpriteName::PLANE_A_2]->setPosition(-100, Utility::getRandomNumber(minimumAltitude2, maximumAltitude2));
		spritePtrs[SpriteManager::SpriteName::PLANE_A_2]->enableSprite();

		lifeDecrementedA1 = FALSE;
		lifeDecrementedA2 = FALSE;
		lifeDecrementedB1 = FALSE;
		lifeDecrementedB2 = FALSE;
	}
}

void PlaneManager::timeBasedManipulation(DWORD deltaTime)
{
	totalTime += deltaTime / 1000.0f;

	if (totalTime < timeForMaxingVelocity)
	{
		// Max time delay before launch is 3.5 seconds, while minimum delay time before launch is 0.5 seconds
		delayTimeBeforeLaunch = 3.5f * (1 - (totalTime/timeForMaxingVelocity)) + 0.5f;
		currentBaseVelocity = minimumPlaneVelocity + (maximumPlaneVelocity - minimumPlaneVelocity)*(totalTime/timeForMaxingVelocity);

	}
}

void PlaneManager::setResetPositionRequired(int32_t value)
{
	assert(value == 1 || value == 2 || value == 3 || value == 4);
	if(value == 1) resetPositionRequiredA1 = TRUE;
	if(value == 2) resetPositionRequiredA2 = TRUE;
	if(value == 3) resetPositionRequiredB1 = TRUE;
	if(value == 4) resetPositionRequiredB2 = TRUE;
}

void PlaneManager::resetPlanes()
{
	resetPositionRequiredA1 = TRUE;
	resetPositionRequiredA2 = TRUE;
	resetPositionRequiredB1 = TRUE;
	resetPositionRequiredB2 = TRUE;

	delayTimeForA1 = 0.0f;
	delayTimeForA2 = 0.0f;
	delayTimeForB1 = 0.0f;
	delayTimeForB2 = 0.0f;

	totalTime = 0.0f;

	currentBaseVelocity = minimumPlaneVelocity;

	lifeDecrementedA1 = TRUE;
	lifeDecrementedA2 = TRUE;
	lifeDecrementedB1 = TRUE;
	lifeDecrementedB2 = TRUE;
}