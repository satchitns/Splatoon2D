#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "SoundSystem.h"

#define BACKGROUND_MUSIC_WAV "Assets/Sounds/LoopingBackgroundMusic.wav"
#define ENTER_SQUID_MODE_WAV "Assets/Sounds/EnterSquidModeSound.wav"
#define EXIT_SQUID_MODE_WAV "Assets/Sounds/ExitSquidModeSound.wav"
#define HIT_PLAYER_WAV "Assets/Sounds/HitPlayerSound.wav"
#define PLAYER_DEATH_WAV "Assets/Sounds/PlayerDeathSound.wav"
#define SHOOT_SOUND_1 "Assets/Sounds/Spray11.wav"
#define SHOOT_SOUND_2 "Assets/Sounds/ShootSound2.wav"
#define NO_DAMAGE_HIT_WAV "Assets/Sounds/OutOfAmmoSound.wav"


class AudioManager
{

public:
	~AudioManager() {};

	static AudioManager* createInstance();
	static AudioManager* getInstance() { return sInstance; }

	void init();
	void update();
	void shutdown();

	void playSound(Sound sound, bool looping);


	Sound GetBackgroundMusic() { return mBackgroundMusic; }
	Sound GetEnterSquidModeSound() { return mEnterSquidModeSound; }
	Sound GetExitSquidModeSound() { return mExitSquidModeSound; }
	Sound GetHitPlayerSound() { return mHitPlayerSound; }
	Sound GetPlayerDeathSound() { return mPlayerDeathSound; }
	Sound GetShootSound1() { return mShootSound1; }
	Sound GetShootSound2() { return mShootSound2; }
	Sound GetNoDamageSound() { return mNoDamageSound; }

private:
	AudioManager() {};

	static AudioManager* sInstance;
	SoundSystem* mSoundSystem;

	Sound fireSound;
	Sound airRaid;


	Sound mBackgroundMusic;
	Sound mEnterSquidModeSound;
	Sound mExitSquidModeSound;
	Sound mHitPlayerSound;
	Sound mPlayerDeathSound;
	Sound mShootSound1;
	Sound mShootSound2;
	Sound mNoDamageSound;

};

#endif