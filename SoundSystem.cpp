#include "SoundSystem.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#include "baseTypes.h"

SoundSystem::SoundSystem()
{
	if (FMOD::System_Create(&mSystem) != FMOD_OK)
	{
		return;
	}
	// Check if the PC has a sound driver
	int driverCount = 0;
	mSystem->getNumDrivers(&driverCount);
	if (driverCount == 0)
	{
		return;
	}
	// Initialize an instance with 12 channels
	mSystem->init(12, FMOD_INIT_NORMAL, nullptr);
};

void SoundSystem::createSound(Sound* pSound, const char* pFile)
{
	mSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound);
}

void SoundSystem::playSound(Sound pSound, bool8_t loop)
{
	if (!loop)
	{
		pSound->setMode(FMOD_LOOP_OFF);
	}
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}

	mSystem->playSound(pSound, 0, false, 0);
}

void SoundSystem::releaseSound(Sound pSound)
{
	pSound->release();
}

void SoundSystem::shutdown()
{
	delete mSystem;
}