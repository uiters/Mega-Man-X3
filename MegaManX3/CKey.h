#pragma once
#include <dinput.h>
#include "GameObject.h"

#define KEYBOARD_BUFFER_SIZE 1024

class CKey
{
protected:
	GameObject* obj;

	LPDIRECTINPUT8       dinput;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

public:
	CKey(GameObject* obj);
	void initKeyboard();

	int isKeyDown(int keyCode);
	void setObject(GameObject* obj);

	void processKeyboard();

	~CKey();
public:
	virtual void keyState(BYTE *) = 0;
	virtual void onKeyDown(int) = 0;
	virtual void onKeyUp(int) = 0;
};

