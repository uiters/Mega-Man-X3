#include "DynamicObject.h"

void DynamicObject::addDamage(int damage)
{
	_levelDamage += 1;
	_damage.push_back(damage);
}

void DynamicObject::setLevelDamage(int level)
{
	_levelDamage = level;
}

int DynamicObject::getDamage()
{
	return _damage.at(_levelDamage);
}

int DynamicObject::getMaxLevelDamage()
{
	return _max - 1;
}


void DynamicObject::setCanDamage(bool canDamage)
{
	_canDamage = canDamage;
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
		_levelDamage = 0;
	}
}
