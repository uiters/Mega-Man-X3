#pragma once
#include "Camera.h"
#include "ConstGlobals.h"
#include "Effect.h"

#define BULLET_COLLISION_STATE_DEFAULT 0

#define BULLET_COLLISION_ID_TEXTURE 9012

class BulletCollision : public Effect
{
public:
	BulletCollision();
	~BulletCollision();
	static BulletCollision* instance;
	static BulletCollision* getInstance();
	void loadResources();
};

