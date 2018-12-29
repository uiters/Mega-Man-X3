#ifndef _DynamicObject_H
#define _DynamicObject_H
#include "GameObject.h"
#include "ConstGlobals.h"
#include "Weapon.h"
#include "Camera.h"
#include "CTime.h"
#include "Effect.h"
class DynamicObject : public GameObject
{
protected:
	bool _death = false;
	vector<Weapon*> _weapons;//animation weapon
	vector<Effect*> _effects;
	float initHP = 0; //for reset
	float initX = 0;
	float initY = 0;
	bool initToLeft = 0;
	CTime timeHide = (2000);
	CRectangle resetBound;
	int timeSwitchColor = 0;
	bool showColor = true;

	bool _attacked = false;
	CTime timeAttacked = (100);
protected:
	virtual void setAnimationDie() {};
	virtual void updateWeapon(DWORD , unordered_map<int, GameObject*>* staticObjects) {};
	virtual void renderWeapon(DWORD dt, D3DCOLOR colorBrush);
	virtual void setResetBound() {}
protected:
	float _hp = 0;
	bool _isReset = true;
public:
	DynamicObject(UINT idTexture, float x, float y, float vx, float vy);
	DynamicObject();

public:
	bool isDeath();
	float* getHp() { return &_hp; }
public:
	
	virtual void receiveDamage(float damage);
	virtual void reset() override;
	virtual vector<Weapon*>* getWeapons();
	virtual void createExplosion(float x, float y) {}
	virtual void setReset() override { _isReset = false; }
};

#endif // !_DynamicObject_H
