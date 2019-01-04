#pragma once
#include <unordered_map>
#include "dsutil.h"
#include "ConstGlobals.h"

using namespace std;
class CSounds
{
private:
	CSoundManager * soundManager;
	static CSounds* _instance;
	CSounds();
	unordered_map<unsigned int, CSound*> sounds;
public:
	void add(UINT idSound, wchar_t* filePath);
	~CSounds();
public:
	void play(UINT idSound, long volume = 0);
	void playInfinity(UINT idSound, long volume = 0);
	void stop(UINT idSound);
	void reset(UINT idSound);
	bool isPlaying(UINT idSound);	

public:
	CSound * get(UINT idSound);
	static CSounds * getInstance();
};

