#include "SpriteManager.h"
#include "baseTypes.h"
#include "openGLFramework.h"
#include "Collider.h"

#include <malloc.h>
#include <windows.h>
#include<assert.h>

SpriteManager* SpriteManager::sInstance = nullptr;

SpriteManager* SpriteManager::createInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new SpriteManager();
	}
	return sInstance;
}

SpriteManager* SpriteManager::getInstance()
{
	return sInstance;
}

void SpriteManager::init()
{
	// Allocate memory for all the sprites
	spritePtrs = (Sprite**)malloc(NUM_SPRITES * sizeof(Sprite*));
	// Generate all sprites for the game
	initBackgroundSpritePtrs();
	initPlaneSpritePtrs();
	initBulletSpritePtrs();
	initTurretSpritePtrs();
	initLivesSpritePtrs();
	initGameEndDisplay();
	// Initialize all sprites
	for (uint8_t i = 0; i < NUM_SPRITES; i++)
	{
		spritePtrs[i]->init();
	}
	// Initialize sprite rotations
	initRotations();
	initColliders();
	spritePtrs[SpriteName::GAME_END]->disableSprite();
	}

void SpriteManager::initBackgroundSpritePtrs()
{
	spritePtrs[SpriteName::BACKGROUND] = new Sprite(0, 0, 1024, 768, "Sprites/Background.png", 0);
	
}

void SpriteManager::initPlaneSpritePtrs()
{
	// Initialize planes for left side
	spritePtrs[SpriteName::PLANE_A_1] = new Sprite(-100, 700, 100, 55, "Sprites/PlaneA.png", 1);
	spritePtrs[SpriteName::PLANE_A_2] = new Sprite(-100, 500, 100, 55, "Sprites/PlaneA.png", 1);
	// Initialize planes for right side
	spritePtrs[SpriteName::PLANE_B_1] = new Sprite(1024, 700, 100, 48, "Sprites/PlaneB.png", 1);
	spritePtrs[SpriteName::PLANE_B_2] = new Sprite(1024, 500, 100, 48, "Sprites/PlaneB.png", 1);
}

void SpriteManager::initBulletSpritePtrs()
{
	// Initialize bullets for turret A
	for (uint8_t i = SpriteName::BULLET_A_1; i <= SpriteName::BULLET_A_3; i++)
	{
		spritePtrs[i] = new Sprite(124, 47, 6, 6, "Sprites/Bullet.png", 2);
	}
	// Initialize bullets for turret B
	for (uint8_t i = SpriteName::BULLET_B_1; i <= SpriteName::BULLET_B_3; i++)
	{
		spritePtrs[i] = new Sprite(890, 47, 6, 6, "Sprites/Bullet.png", 2);
	}
}

void SpriteManager::initTurretSpritePtrs()
{
	// Initialize turret barrels
	spritePtrs[SpriteName::TURRET_A] = new Sprite(127, 50, 41, 78, "Sprites/TurretNew.png", 3);
	spritePtrs[SpriteName::TURRET_B] = new Sprite(893, 50, 41, 78, "Sprites/TurretNew.png", 3);
	// Initialize turret bases
	spritePtrs[SpriteName::TURRET_BASE_A] = new Sprite(100, 35, 57, 53, "Sprites/TurretBase.png", 4);
	spritePtrs[SpriteName::TURRET_BASE_B] = new Sprite(867, 35, 57, 53, "Sprites/TurretBase.png", 4);

}

void SpriteManager::initLivesSpritePtrs()
{

	spritePtrs[SpriteName::LIFE_A_1] = new Sprite(10, 5, 20, 20, "Sprites/LivesA.png", 3);
	spritePtrs[SpriteName::LIFE_A_2] = new Sprite(40, 5, 20, 20, "Sprites/LivesA.png", 3);
	spritePtrs[SpriteName::LIFE_A_3] = new Sprite(70, 5, 20, 20, "Sprites/LivesA.png", 3);
	spritePtrs[SpriteName::LIFE_A_4] = new Sprite(100, 5, 20, 20, "Sprites/LivesA.png", 3);
	spritePtrs[SpriteName::LIFE_A_5] = new Sprite(130, 5, 20, 20, "Sprites/LivesA.png", 3);

	spritePtrs[SpriteName::LIFE_B_1] = new Sprite(1024-30, 5, 20, 20, "Sprites/LivesB.png", 3);
	spritePtrs[SpriteName::LIFE_B_2] = new Sprite(1024 - 60, 5, 20, 20, "Sprites/LivesB.png", 3);
	spritePtrs[SpriteName::LIFE_B_3] = new Sprite(1024-90, 5, 20, 20, "Sprites/LivesB.png", 3);
	spritePtrs[SpriteName::LIFE_B_4] = new Sprite(1024-120, 5, 20, 20, "Sprites/LivesB.png", 3);
	spritePtrs[SpriteName::LIFE_B_5] = new Sprite(1024-150, 5, 20, 20, "Sprites/LivesB.png", 3);
}

void SpriteManager::initGameEndDisplay()
{
	spritePtrs[SpriteName::GAME_END] = new Sprite(0, 268, 1024, 500, "Sprites/GameEnd.png", 4);
}

void SpriteManager::initRotations()
{
	// Rotate turrets such that they face towards center on starting the game
	spritePtrs[SpriteName::TURRET_A]->setRotation(5.0f);
	spritePtrs[SpriteName::TURRET_B]->setRotation(45.0f);
}

void SpriteManager::initColliders()
{
	// Colliders for planes
	spritePtrs[SpriteName::PLANE_A_1]->createCollider(0, 20, 100, 35, ColliderTag::PLANE_A, spritePtrs[SpriteName::PLANE_A_1]);
	spritePtrs[SpriteName::PLANE_A_2]->createCollider(0, 20, 100, 35, ColliderTag::PLANE_A, spritePtrs[SpriteName::PLANE_A_2]);
	
	spritePtrs[SpriteName::PLANE_B_1]->createCollider(0, 20, 100, 28, ColliderTag::PLANE_B, spritePtrs[SpriteName::PLANE_B_1]);
	spritePtrs[SpriteName::PLANE_B_2]->createCollider(0, 20, 100, 28, ColliderTag::PLANE_B, spritePtrs[SpriteName::PLANE_B_2]);
	// Colliders for bullets
	for (uint8_t i = SpriteName::BULLET_A_1; i <= SpriteName::BULLET_A_3; i++)
	{
		spritePtrs[i]->createCollider(0, 0, 6, 6, ColliderTag::BULLET_A, spritePtrs[i]);
	}
	
	for (uint8_t i = SpriteName::BULLET_B_1; i <= SpriteName::BULLET_B_3; i++)
	{
		spritePtrs[i]->createCollider(0, 0, 6, 6, ColliderTag::BULLET_B, spritePtrs[i]);
	}
}

void SpriteManager::update(DWORD milliseconds)
{
	currentFrameTime = milliseconds;
	for (uint8_t i = 0; i < NUM_SPRITES; i++)
	{
		spritePtrs[i]->updateSprite(milliseconds);
	}
}

void SpriteManager::renderSprites()
{
	for (uint8_t i = 0; i < NUM_SPRITES; i++)
	{
		spritePtrs[i]->render();
	}
	//spritePtrs[SpriteName::PLANE_A_1]->getCollider()->renderCollider();
}

void SpriteManager::shutDown()
{
	for (uint8_t i = 0; i < NUM_SPRITES; i++)
	{
		delete spritePtrs[i];
	}
	free(spritePtrs);
}

Sprite** SpriteManager::getSpritePtrs()
{
	return spritePtrs;
}

int32_t SpriteManager::getNumberOfSprites()
{
	return NUM_SPRITES;
}

void  SpriteManager::resetSprites()
{
	for (uint8_t i = 0; i < NUM_SPRITES; i++)
	{
		spritePtrs[i]->setRotation(0);
		spritePtrs[i]->setVelocity(0, 0);
		spritePtrs[i]->enableSprite();
	}
	spritePtrs[SpriteName::PLANE_A_1]->setPosition(-100, 700);
	spritePtrs[SpriteName::PLANE_A_2]->setPosition(-100, 500);
	spritePtrs[SpriteName::PLANE_B_1]->setPosition(1024, 700);
	spritePtrs[SpriteName::PLANE_B_2]->setPosition(1024, 500);
	for (uint8_t i = SpriteName::BULLET_A_1; i <= SpriteName::BULLET_A_3; i++)
	{
		spritePtrs[i]->setPosition(124, 47);
	}
	for (uint8_t i = SpriteName::BULLET_B_1; i <= SpriteName::BULLET_B_3; i++)
	{
		spritePtrs[i]->setPosition(890,47);
	}
	initRotations();
	spritePtrs[SpriteName::GAME_END]->disableSprite();
}