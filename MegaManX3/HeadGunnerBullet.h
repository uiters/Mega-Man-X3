#pragma once
#include <stdlib.h>
#include "Weapon.h"
#include "ConstGlobals.h"
#include "Camera.h"
#include "CollisionEvent.h"
#include "Brick.h"


#define HEAD_GUNNER_BULLET_GRAVITY 0.01f
#define HEAD_GUNNER_BULLET_SPEED_X 0.12f
#define HEAD_GUNNER_BULLET_SPEED_Y -0.15f

class HeadGunnerBullet : public Weapon
{
public:
	bool nx;
	bool ny;

	HeadGunnerBullet(float x, float y, bool nx, bool ny);
	HeadGunnerBullet(int id, float x, float y, bool nx, bool ny);
	~HeadGunnerBullet();
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void setState(int state);
	void loadResources();
	void setPosition(float x, float y);
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;

private:
	void collisionStatic(unordered_map<int, GameObject*>* staticObjects);
};

