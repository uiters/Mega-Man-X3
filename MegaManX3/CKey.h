#ifndef _CKey_H_
#define _CKey_H_

#include <Windows.h>
#include <dinput.h>

#include "Game.h"

#define KEYBOARD_BUFFER_SIZE 1024
#define DIRECTINPUT_VERSION 0x0800
class CKey
{
protected:
	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

public:
	int isKeyDown(int keyCode);
	void processKeyboard();

public:
	virtual void keyState(BYTE *) = 0;
	virtual void onKeyDown(int) = 0;
	virtual void onKeyUp(int) = 0;
};

#endif // !_CKey_H_