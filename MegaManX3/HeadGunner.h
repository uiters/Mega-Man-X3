#pragma once
#include<vector>

#include "DynamicObject.h"
#include "Camera.h"

#include "HeadGunnerBullet.h"
#include "HeadGunnerBullet2.h"

#include "BulletCollision.h"
#include "WallSlide.h"

#define HEAD_GUNNER_STATE_DEFAULT 0
#define HEAD_GUNNER_STATE_SHOT_TOP 100
#define HEAD_GUNNER_STATE_SHOT_BOTTOM 200
#define HEAD_GUNNER_STATE_SHOT_LEFT 300 // 2 times
#define HEAD_GUNNER_STATE_SHOT_RIGHT 400
#define HEAD_GUNNER_STATE_DIE 500

#define HEAD_GUNNER_ID_TEXTURE 702

class HeadGunner :
	public DynamicObject
{
public:
	HeadGunner(UINT id, float x, float y, bool nx);
	~HeadGunner();

public:
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0) override;
	void updateWeapon(DWORD, unordered_map<int, GameObject*>*) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void loadResources() override;
	void createExplosion(float x, float y) override;
	void setAnimationDie() override;

private:
	void calculateDie();
	void setState(int state);

private:
	bool nx;
	int repeat;
	PointF die[4];
	WallSlide* shotEffect = WallSlide::getInstance();
	BulletCollision* collisionEffect = BulletCollision::getInstance();
	void setResetBound() override;

private:
	void createBullet();
	void createBullet2();
	void renderDie(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void renderNormal(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
};

