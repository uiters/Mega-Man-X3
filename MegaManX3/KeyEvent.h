#pragma once
#include "KeyEventHander.h"
#include "GameObject.h"

class KeyEvent: public KeyEventHandler
{
private:
	GameObject* main = NULL;
public:
	KeyEvent(GameObject* mainGame) : main(mainGame){}
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	~KeyEvent();
};


