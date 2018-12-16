#include "DynamicObject.h"







DynamicObject::DynamicObject(UINT idTexture, float x, float y, float vx, float vy) : GameObject(idTexture, x, y, vx, vy)
{
}

DynamicObject::DynamicObject()
{
	_death = false;
	_canReset = true;
	canAttack = true;
}


int DynamicObject::getDamage()
{
	return baseDamage;
}

bool DynamicObject::isDeath()
{
	return _death;
}

void DynamicObject::receiveDamage(int damage)
{
	if (hp > 0)
		hp -= damage;
	if (hp < 0)
		_death = true;
}

void DynamicObject::reset()
{
	if (_canReset)
	{
		hp = _hp;
		_death = false;
		visible = true;
	}
}

vector<Weapon*>* DynamicObject::getWeapons()
{
	return &_weapons;
}

