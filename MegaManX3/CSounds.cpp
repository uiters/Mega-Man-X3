#include "CSounds.h"



CSounds::CSounds()
{
	soundManager = soundManagerGlobal;
}


void CSounds::add(UINT idSound, wchar_t* filePath)
{
	HRESULT result;

	CSound *wave;

	result = soundManager->Create(&wave, filePath, DSBCAPS_CTRLVOLUME);
	if (result != DS_OK)
	{
		debugOut(L"[Failed] Can not load sound file");
		return;
	}
	sounds[idSound] = wave;
}

CSounds::~CSounds()
{
}

CSounds * CSounds::_instance = nullptr;

CSounds * CSounds::getInstance()
{
	if (!_instance) _instance = new CSounds();
	return _instance;
}

void CSounds::play(UINT idSound, long volume)
{
	sounds[idSound]->Play(0, 0, volume);
}

void CSounds::playInfinity(UINT idSound, long volume)
{
	sounds[idSound]->Play(0, DSBPLAY_LOOPING, volume);

}
void CSounds::stop(UINT idSound)
{
	sounds[idSound]->Stop();
}

void CSounds::reset(UINT idSound)
{
	sounds[idSound]->Reset();
}

bool CSounds::isPlaying(UINT idSound)
{
	return sounds[idSound]->IsSoundPlaying();
}

CSound* CSounds::get(UINT idSound)
{
	return sounds[idSound];
}