#pragma once
#include "Weapon.h"
#include "Camera.h"
class ChargedShot1 :
	public Weapon
{
private:
	void loadResources() override;
public:
	ChargedShot1(float x, float y, bool toLeft);
	~ChargedShot1();
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
};

