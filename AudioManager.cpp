#include "AudioManager.h"
#include "baseTypes.h"
#include "SoundSystem.h"

int potato = 0;
AudioManager* AudioManager::sInstance = nullptr;

AudioManager* AudioManager::createInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new AudioManager();
		sInstance->mSoundSystem = new SoundSystem();
	}
	return sInstance;
}

void AudioManager::init()
{
	
	mSoundSystem->createSound(&mBackgroundMusic, BACKGROUND_MUSIC_WAV);
	mSoundSystem->createSound(&mEnterSquidModeSound, ENTER_SQUID_MODE_WAV);
	mSoundSystem->createSound(&mExitSquidModeSound, EXIT_SQUID_MODE_WAV);
	mSoundSystem->createSound(&mHitPlayerSound, HIT_PLAYER_WAV);
	mSoundSystem->createSound(&mPlayerDeathSound, PLAYER_DEATH_WAV);
	mSoundSystem->createSound(&mShootSound1, SHOOT_SOUND_1);
	mSoundSystem->createSound(&mShootSound2, SHOOT_SOUND_2);
	mSoundSystem->createSound(&mNoDamageSound, NO_DAMAGE_HIT_WAV);
}

void AudioManager::update()
{

}

void AudioManager::shutdown()
{
	// Release sounds
	mSoundSystem->releaseSound(mBackgroundMusic);
	mSoundSystem->releaseSound(mEnterSquidModeSound);
	mSoundSystem->releaseSound(mExitSquidModeSound);
	mSoundSystem->releaseSound(mHitPlayerSound); 
	mSoundSystem->releaseSound(mPlayerDeathSound);
	mSoundSystem->releaseSound(mShootSound1);
	mSoundSystem->releaseSound(mShootSound2);
	mSoundSystem->releaseSound(mNoDamageSound);
}


void AudioManager::playSound(Sound sound, bool looping)
{
	mSoundSystem->playSound(sound, looping);
}