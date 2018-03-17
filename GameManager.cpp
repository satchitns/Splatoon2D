#include "GameManager.h"
#include "basetypes.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "game.h"

#include <assert.h>
#include <windows.h>
#include <time.h>

GameManager* GameManager::sInstance = nullptr;
const float_t GameManager::timeForReload = 0.7f;

GameManager* GameManager::createInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new GameManager();
	}
	return sInstance;
}

void GameManager::init()
{
	srand(time(NULL));
	gameEnd = FALSE;
	numberOfBulletsFiredA = 0;
	numberOfBulletsFiredB = 0;
	reloadRequiredA = FALSE;
	reloadRequiredB = FALSE;
	timeSpentReloadingA = 0.0f;
	timeSpentReloadingB = 0.0f;
	livesLeftA = 5;
	livesLeftB = 5;
}

void GameManager::update(DWORD deltaTime)
{
	reloadTurrets(deltaTime);
	resetBullets();
	displayGameEndScreen();
}

uint8_t GameManager::getNumberOfBulletsFired(uint8_t character)
{
	assert(character == 'A' || character == 'B');
	if (character == 'A')
	{
		return numberOfBulletsFiredA;
	}
	else if (character == 'B')
	{
		return numberOfBulletsFiredB;
	}
}

void GameManager::incrementNumberOfBulletsFired(uint8_t character)
{
	assert(character == 'A' || character == 'B');
	if (character == 'A')
	{
		numberOfBulletsFiredA++;
		reloadRequiredA = TRUE;
		// If turret A is empty, reset the counter for new set of bullets
		if (numberOfBulletsFiredA == 3) numberOfBulletsFiredA = 0;
	}
	else if (character == 'B')
	{
		numberOfBulletsFiredB++;
		reloadRequiredB = TRUE;
		// If turret B is empty, reset the counter for new set of bullets
		if (numberOfBulletsFiredB == 3) numberOfBulletsFiredB = 0;
	}
	
}

bool8_t GameManager::getReloadRequired(uint8_t character)
{
	assert(character == 'A' || character == 'B');
	if (character == 'A')
	{
		return reloadRequiredA;
	}
	else if (character == 'B')
	{
		return reloadRequiredB;
	}
}

void GameManager::reloadTurrets(DWORD deltaTime)
{
	if (reloadRequiredA)
	{
		timeSpentReloadingA += (deltaTime / 1000.0f);
		if (timeSpentReloadingA > timeForReload)
		{
			timeSpentReloadingA = 0.0f;
			reloadRequiredA = FALSE;
		}
	}
	if (reloadRequiredB)
	{
		timeSpentReloadingB += (deltaTime / 1000.0f);
		if (timeSpentReloadingB > timeForReload)
		{
			timeSpentReloadingB = 0.0f;
			reloadRequiredB = FALSE;
		}
	}
}

void GameManager::resetBullets()
{
	Sprite** spritePtrs = SpriteManager::getInstance()->getSpritePtrs();
	for (uint8_t i = SpriteManager::SpriteName::BULLET_A_1; i <= SpriteManager::SpriteName::BULLET_B_3; i++)
	{
		if (spritePtrs[i]->getPosition()->y > CGame::mScreenHeight)
		{
			resetBullet(spritePtrs[i], i);
		}
	}
}

void GameManager::resetBullet(Sprite* bulletSprite, uint8_t position)
{
	if (position <= SpriteManager::SpriteName::BULLET_A_3)
	{
		bulletSprite->setVelocity(0, 0);
		bulletSprite->setPosition(124, 47);
	}
	else
	{
		bulletSprite->setVelocity(0, 0);
		bulletSprite->setPosition(890, 47);
	}
}

void GameManager::decrementLife(char8_t player)
{
	assert(player == 'A' || player == 'B');
	if (gameEnd)
	{
		return;
	}

	Sprite** spritePtrs = SpriteManager::getInstance()->getSpritePtrs();

	if (player == 'A')
	{
		livesLeftA--;
		spritePtrs[SpriteManager::SpriteName::LIFE_A_1 + livesLeftA]->disableSprite();
		if (livesLeftA == 0)
		{
			gameEnd = TRUE;
		}
	}
	if (player == 'B')
	{
		livesLeftB--;
		spritePtrs[SpriteManager::SpriteName::LIFE_B_1 + livesLeftB]->disableSprite();
		if (livesLeftB == 0)
		{
			gameEnd = TRUE;
		}
	}
}

bool8_t GameManager::getGameEnd()
{
	return gameEnd;
}

void GameManager::displayGameEndScreen()
{
	if (!gameEnd)
	{
		return;
	}
	Sprite** spritePtrs = SpriteManager::getInstance()->getSpritePtrs();
	spritePtrs[SpriteManager::SpriteName::GAME_END]->enableSprite();
}

void GameManager::resetGameEnd()
{
	gameEnd = FALSE;
}