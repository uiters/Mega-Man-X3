#ifndef _WeaponEffectController_H_
#define _WeaponEffectController_H_
#include "WallSlide.h"
#include "DashSmoke.h"
class WeaponEffectController
{
private:
	WeaponEffectController();
	static WeaponEffectController* _instance;
	WallSlide* smoke;
public:
	static WeaponEffectController* getIntance();
	~WeaponEffectController();
public:
	void createBulletSmoke(float x, float y);
	void createBusterEffect(float x, float y);
	void createCharged1Effect(float x, float y);

public:
	void render(DWORD dt);
};

#endif //!_WeaponEffectController_H_