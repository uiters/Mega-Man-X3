#ifndef _DynamicObject_H
#define _DynamicObject_H
#include "GameObject.h"
#include "Weapon.h"
class DynamicObject : public GameObject
{
protected:
	bool _death = false;
	vector<Weapon*> _weapon;//animation weapon

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
};

#endif // !_DynamicObject_H
