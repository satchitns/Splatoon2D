// Plane manager controls the spawnning of planes, their speeds, etc.

#ifndef PLANEBEHAVIOUR_H
#define PLANEBEHAVIOUR_H

#include "baseTypes.h"

#include <windows.h>

class PlaneManager
{

public:
	~PlaneManager() {};

	static PlaneManager* createInstance();
	static PlaneManager* getInstance();

	void init();
	void update(DWORD deltaTime);
	// Sets resetPositionRequired boolean for appropriate sprite
	void setResetPositionRequired(int32_t);
	// Planes are reset while the game is restarted
	void resetPlanes();
private:
	PlaneManager() {};

	static PlaneManager* sInstance;
	
	// Constants which affect plane velocities over time
	static const float_t minimumPlaneVelocity;
	static const float_t maximumPlaneVelocity;
	static const float_t timeForMaxingVelocity;

	// Total time spent since instantiation of the plane manager
	float_t totalTime;
	float_t currentBaseVelocity;

	// Altitude ranges for two tiers of planes
	static const int32_t minimumAltitude1;
	static const int32_t maximumAltitude1;
	
	static const int32_t minimumAltitude2;
	static const int32_t maximumAltitude2;

	// The time delay for respawning of next wave of planes
	static float_t delayTimeBeforeLaunch;

	// Time spent before relaunch for each plane
	float_t delayTimeForA1;
	float_t delayTimeForA2;
	float_t delayTimeForB1;
	float_t delayTimeForB2;

	// If a plane is out of display and resetting the position is required
	bool8_t resetPositionRequiredA1;
	bool8_t resetPositionRequiredA2;
	bool8_t resetPositionRequiredB1;
	bool8_t resetPositionRequiredB2;

	// Boolean to ensure that life is decremented only once per fail case
	bool8_t lifeDecrementedA1;
	bool8_t lifeDecrementedA2;
	bool8_t lifeDecrementedB1;
	bool8_t lifeDecrementedB2;
	// If a plane is ready to launch
	bool8_t launchPlaneA1;
	bool8_t launchPlaneA2;
	bool8_t launchPlaneB1;
	bool8_t launchPlaneB2;
	// Checks for each plane if it requires to be reset
	void checkIfResetIsRequired();
	// Checks if all planes have waited the delay period before launch
	void checkIfPlanesShouldBeLaunched(DWORD deltaTime);
	// Launches the planes
	void launchPlanes();
	// Gameplay variables are affected over time
	void timeBasedManipulation(DWORD deltaTime);
};

#endif