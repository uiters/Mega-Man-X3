#pragma once
#include <map>
#include "dxsound.h"
#include "ConstGlobals.h"
enum eSoundID
{

};

class Sound
{
private:
	std::map<eSoundID, CSound*> listSound;
	Sound();
	static Sound* instance;
public:

	~Sound();
	static Sound* getInstance();
	void loadSound();
	void play(eSoundID);
	void stop(eSoundID);
	void playLoop(eSoundID);
	bool isPLaying(eSoundID);
};

