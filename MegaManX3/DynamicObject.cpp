#include "DynamicObject.h"



void DynamicObject::addWeapon(WeaponID idWeapon)
{
	_weapon.push_back(idWeapon);
}

DynamicObject::DynamicObject(UINT idTexture, float x, float y, float vx, float vy): GameObject(idTexture, x, y, vx, vy)
{

}

DynamicObject::DynamicObject()
{
	_death = false;
	_canReset = true;
	_currentWeapon = 0;
	canAttack = true;
}

void DynamicObject::setWeapon(WeaponID idWeapon)
{
	_currentWeapon = idWeapon;
}

int DynamicObject::getDamage()
{
	return baseDamage;
}

int DynamicObject::getMaxWeapon()
{
	return _weapon.size();
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
		_currentWeapon = 0;
	}
}
