
#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "Sprite.h"
#include "openGLFramework.h"
#include "Collider.h"

#include <windows.h>

class SpriteManager
{
public:
	~SpriteManager() {};

	enum SpriteName
	{
		BACKGROUND,
		PLANE_A_1,
		PLANE_A_2,
		PLANE_B_1,
		PLANE_B_2,
		BULLET_A_1,
		BULLET_A_2,
		BULLET_A_3,
		BULLET_B_1,
		BULLET_B_2,
		BULLET_B_3,
		TURRET_A,
		TURRET_B,
		TURRET_BASE_A,
		TURRET_BASE_B,
		LIFE_A_1,
		LIFE_A_2,
		LIFE_A_3,
		LIFE_A_4,
		LIFE_A_5,
		LIFE_B_1,
		LIFE_B_2,
		LIFE_B_3,
		LIFE_B_4,
		LIFE_B_5,
		GAME_END
	};

	static SpriteManager* createInstance();
	static SpriteManager* getInstance();

	void init();
	void update(DWORD milliseconds);
	void renderSprites();
	void shutDown();

	// Reset method is called at restarting of the game
	void resetSprites();

	Sprite** getSpritePtrs();
	static int32_t getNumberOfSprites();

private:
	SpriteManager() {};

	DWORD currentFrameTime;

	Sprite** spritePtrs;
	static SpriteManager* sInstance;
	static const uint8_t NUM_SPRITES = 26;

	void initBackgroundSpritePtrs();
	void initPlaneSpritePtrs();
	void initBulletSpritePtrs();
	void initTurretSpritePtrs();
	void initLivesSpritePtrs();
	void initGameEndDisplay();

	void initRotations();
	void initColliders();

};

#endif
