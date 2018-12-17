#include "DynamicObject.h"
#include "ExplosionEffect.h"






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
	//DWORD dt = GetTickCount();
	//if (dt - delayReciveDamage > 100)//receive
	//{
		if (_hp > 0)
			_hp -= damage;
		if (_hp <= 0)
		{
			setAnimationDie();
			_death = true;
		}
	//}


}

void DynamicObject::reset()
{
	if (_canReset)
	{
		_hp = hp;
		_death = false;
		visible = true;
	}
}

vector<Weapon*>* DynamicObject::getWeapons()
{
	return &_weapons;
}



