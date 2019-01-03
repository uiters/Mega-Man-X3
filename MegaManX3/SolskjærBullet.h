#pragma once
#include<vector>
#include <stdlib.h>

#include "Weapon.h"
#include "Camera.h"
#include "ConstGlobals.h"
#include "CollisionEvent.h"
#include "Brick.h"


#define SOLSKJÆR_BULLET_SPEED_X -0.055f;
#define SOLSKJÆR_BULLET_SPEED_Y 0.05f

#define SOLSKJÆR_BULLET_STATE_ONLY 0

#define SOLSKJÆR_BULLET_ID_TEXTURE 337

class SolskjærBullet : public Weapon
{
public:
	SolskjærBullet(float x, float y);
	~SolskjærBullet();
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void setPosition(float x, float y);
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;

private:
	SolskjærBullet* clone;
	bool isClone;
	int counter;
	bool isOnly;

	void setState(int state);
	void loadResources();
	void collisionStatic(unordered_map<int, GameObject*>* staticObjects);
};

