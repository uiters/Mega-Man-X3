#include "sound.h"

Sound::Sound() {}
Sound::~Sound() {}

Sound* Sound::instance;

Sound* Sound::getInstance()
{
	if (instance == 0)
		instance = new Sound();
	return instance;
}

void Sound::loadSound()
{
	InitDirectSound(hWndGlobal);
	

}

void Sound::play(eSoundID id)
{
	auto sound = listSound[id];
	if (sound != NULL)
		PlaySound(sound);
}

void Sound::playLoop(eSoundID id)
{
	auto sound = listSound[id];
	if (sound != NULL)
		LoopSound(sound);
}

void Sound::stop(eSoundID id)
{
	auto sound = listSound[id];
	if (sound != NULL)
		StopSound(sound);
}

bool Sound::isPLaying(eSoundID id)
{
	auto sound = listSound[id];
	if (sound != NULL)
		return sound->IsSoundPlaying();
	return false;
}