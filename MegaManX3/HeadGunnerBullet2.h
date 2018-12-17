#pragma once
#include <stdlib.h>
#include "Weapon.h"
#include "ConstGlobals.h"
#include "Camera.h"
#include "CollisionEvent.h"
#include "Brick.h"

#define HEAD_GUNNER_BULLET2_SPEED_X 0.12f
#define HEAD_GUNNER_BULLET2_SPEED_Y 0

#define HEAD_GUNNER_BULLET2_STATE_DEFAULT 0

#define HEAD_GUNNER_BULLET2_ID_TEXTURE 873

class HeadGunnerBullet2 : public Weapon
{
public:
	bool isDelete;
	bool nx;
	bool ny;

	HeadGunnerBullet2(float x, float y, bool nx, bool ny);
	~HeadGunnerBullet2();
	void update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects = 0, unordered_map<int, CTreeObject*>* dynamicObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void setState(int state);
	void loadResources();
	void setPosition(float x, float y);
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;

private:
	void collisionStatic(unordered_map<int, CTreeObject*>* staticObjects);
};

