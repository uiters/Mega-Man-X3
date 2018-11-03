#pragma once
#include "CKey.h"
class KeyEvent :
	public CKey
{
public:
	KeyEvent(GameObject* obj = 0);
	~KeyEvent();

public:
	void keyState(BYTE*) override;
	void onKeyDown(int) override;
	void onKeyUp(int) override;
};

