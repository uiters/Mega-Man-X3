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
	int _hp = 0; //for reset
	int baseDamage;
public:
	int hp = 0;
	bool canMove = true;
	bool canControl = false;
public:
	DynamicObject(UINT idTexture, float x, float y, float vx, float vy);
	DynamicObject();
	int getDamage();
	bool isDeath();

public:
	virtual GameObject* clone(int id, int x, int y) = 0;
	virtual void getBoundingBox(float & left, float & top, float & right, float & bottom) override = 0;
	virtual void receiveDamage(int damage);
	virtual void reset();
	virtual vector<Weapon*>* getWeapons();
	virtual void createExplosion(float x, float y) {}
};

#endif // !_DynamicObject_H
