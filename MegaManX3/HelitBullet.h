#pragma once
#include "Weapon.h"
class HelitBullet :
	public Weapon
{
private:
	void loadResources() override;
public:
	HelitBullet(int x, int y, bool toLeft);
	~HelitBullet();
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	virtual void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0) override;
	virtual void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
};

