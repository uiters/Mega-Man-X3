#pragma once
#include "Weapon.h".
#include "Camera.h"
class ChargedShot2 :
	public Weapon
{
private:
	void loadResources() override;
public:
	ChargedShot2(float x, float y, bool toLeft);
	~ChargedShot2();
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
};

