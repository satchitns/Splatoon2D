#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "baseTypes.h"
#include "Sprite.h"

#include <windows.h>

class GameManager
{

public:
	~GameManager() {};

	// Creates the singleton instance of Game Manager class
	static GameManager* createInstance();
	// Returns the instance of the Game Manager class
	static GameManager* getInstance() { return sInstance; }
	// Initialize variables for the Game Manager singleton
	void init();
	// This method is executed each frame
	void update(DWORD);

	// Returns the number of bullets fired by the turret
	uint8_t getNumberOfBulletsFired(uint8_t);
	// Returns if the turret requires reloading
	bool8_t getReloadRequired(uint8_t);
	// Increments the number of bullets fired / resets the number of bullets
	void incrementNumberOfBulletsFired(uint8_t);
	// Resets the position and velocity of a bullet
	void resetBullet(Sprite*, uint8_t position);
	// Decrement's the lives left of the player on losing a point
	void GameManager::decrementLife(char8_t player);
	// Resets game end boolean when game is restarted
	void resetGameEnd();

	bool8_t getGameEnd();
	
	void displayGameEndScreen();

private:

	GameManager() {};

	// The singleton instance of the Game Manager class
	static GameManager* sInstance;
	// Amount of time required to reload a turret bullet
	static const float_t timeForReload;

	// Number of bullets that have been fired by the turret
	uint8_t	numberOfBulletsFiredA;
	uint8_t numberOfBulletsFiredB;
	// If a bullet is fired and a reload is required
	bool8_t reloadRequiredA;
	bool8_t reloadRequiredB;
	// The amount of time already spent in the reloading process
	float_t timeSpentReloadingA;
	float_t timeSpentReloadingB;
	// Number of lives of player A and B
	int32_t livesLeftA;
	int32_t livesLeftB;

	bool8_t gameEnd;
	
	// If a turret required reloading, calculate if the turret waited for appropriate time
	void reloadTurrets(DWORD);
	// Loops through all the bullets are resets all those which are out of display
	void resetBullets();
};

#endif