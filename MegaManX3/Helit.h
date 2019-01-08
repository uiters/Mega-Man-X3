#ifndef _Helit_H_
#define _Helit_H_
#include "DynamicObject.h"
#include "HelitBullet.h"
#include "WallSlide.h"
#include "ExplosionEffect.h"
#define HELIT_EFFECT_FIRE 0
#define HELIT_EFFECT_EXPLOSION 1
#include <cstdlib>
#include <ctime>

class Helit :
	public DynamicObject
{
private:
	Helit();

	UINT body = 0;
	CTime timeFire = (5000);
	PointF dieX[3];
	
	CTime timeChangeDirection = (600);
	bool flyUp = true;

	int timeSwitchBody = 0;

public:
	Helit(int id, float x, float y, bool toLeft);
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0) override;
	void updateWeapon(DWORD dt, unordered_map<int, GameObject*>* staticObjects) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	~Helit();

private:
	void calculateDie();
	void setAnimationDie();
	void renderDie(DWORD dt);
	void renderNormal(DWORD dt);
	void setAnimationFire();
	void loadSprites();
	void loadResources() override;
	void setResetBound() override;

	bool collisionBulletStatic(Weapon* bullet, unordered_map<int, GameObject*>* staticObjects);
public:
	void createExplosion(float x, float y) override;
};

#endif // !_Helit_H_