#pragma once
#include <dinput.h>
#include "ConstGlobals.h"
#include "Debugs.h"
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
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
