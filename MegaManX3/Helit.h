#ifndef _Helit_H_
#define _Helit_H_
#include "DynamicObject.h"
#include "HelitBullet.h"
#include "WallSlide.h"
#include "ExplosionEffect.h"
#define HELIT_EFFECT_FIRE 0
#define HELIT_EFFECT_EXPLOSION 1
class Helit :
	public DynamicObject
{
private:
	Helit();
	void loadSprites();
	void loadResources() override;
	UINT body = 0;
	CTime timeDeath = (50000);
	CTime timeFire = (1000);
	PointF dieX[3];
	bool showColor = true;
	int timeSwitchColor = 0;
	int timeSwitchBody = 0;

public:
	Helit(int id, float x, float y, bool toLeft);
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	Helit* clone(int id, int x, int y) override;
	void update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects = 0, unordered_map<int, CTreeObject*>* dynamicObjects = 0) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	~Helit();

private:
	void calculateDie();
	void setAnimationDie();
	void renderDie(DWORD dt);

	void renderNormal(DWORD dt);
	void setAnimationFire();

	void updateBullet(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects);
	bool collisionBulletStatic(Weapon* bullet, unordered_map<int, CTreeObject*>* staticObjects);

public:
	void createExplosion(float x, float y);
	vector<Weapon*>* getWeapons();
};

#endif // !_Helit_H_