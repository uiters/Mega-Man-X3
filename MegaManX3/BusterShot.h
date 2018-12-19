#pragma once
#include "Weapon.h"
#include "Camera.h"
class BusterShot :
	public Weapon
{
private:
	void loadResources() override;
public:
	BusterShot(float x, float y, bool toLeft);
	~BusterShot();
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects);
};

