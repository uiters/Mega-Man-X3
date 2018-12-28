#ifndef _WeaponEffectController_H_
#define _WeaponEffectController_H_
#include "WallSlide.h"
#include "DashSmoke.h"
#include "Charged1Collision.h"
#include "Charged2Collision.h"
#include "BusterCollision.h"
class WeaponEffectController
{
private:
	WeaponEffectController();
	static WeaponEffectController* _instance;
	WallSlide* smoke;
	BusterCollision*   buster;
	Charged1Collision* charged1;
	Charged2Collision* charged2;
public:
	static WeaponEffectController* getIntance();
	~WeaponEffectController();
public:
	void createBulletSmoke(float x, float y);
	void createBusterEffect(float x, float y, bool toLeft);
	void createCharged1Effect(float x, float y, bool toLeft);
	void createCharged2Effect(float x, float y, bool toLeft);
public:
	void render(DWORD dt);
};

#endif //!_WeaponEffectController_H_