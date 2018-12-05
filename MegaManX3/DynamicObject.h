#ifndef _DynamicObject_H
#define _DynamicObject_H
#include "GameObject.h"
#include "Weapon.h"
class DynamicObject
	:public GameObject
{
protected:
	bool _death = false;
	vector<WeaponID> _weapon;//animation weapon

	int _hp = 0; //for reset
	int _currentWeapon;
	int baseDamage;

	void addWeapon(WeaponID idWeapon);

public:
	int hp = 0;
	bool canMove = true;
	bool canControl = false;

public:
	DynamicObject(UINT idTexture, float x, float y, float vx, float vy);
	DynamicObject();
	void setWeapon(WeaponID idWeapon);
	int getDamage();
	int getMaxWeapon();

	bool isDeath();

public:
	virtual void receiveDamage(int damage);
	virtual void reset();
	
};

#endif // !_DynamicObject_H
