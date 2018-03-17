#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include "fmod.hpp"
#include "fmod_errors.h"
#include "baseTypes.h"

typedef FMOD::Sound* Sound;

class SoundSystem
{
public:
	SoundSystem();

	void createSound(Sound* pSound, const char* pFile);
	void playSound(Sound pSound, bool8_t loop);
	void releaseSound(Sound pSound);

private:
	FMOD::System* mSystem;
	void SoundSystem::shutdown();
};

#endif