#include "DynamicObject.h"
#include "ExplosionEffect.h"

void DynamicObject::renderWeapon(DWORD dt, D3DCOLOR colorBrush)
{
	int size = _weapons.size();
	for (int i = 0; i < size; ++i)
	{
		_weapons[i]->render(dt);
	}
}

DynamicObject::DynamicObject(UINT id, float x, float y, float vx, float vy) : GameObject(id, x, y, vx, vy)
{
	this->initX = x;
	this->initY = y;
	_death = false;
	visible = true;
}

DynamicObject::DynamicObject()
{
	_death = false;
}


bool DynamicObject::isDeath()
{
	return _death;
}

void DynamicObject::receiveDamage(float damage)
{
	if (_hp > 0)
	{
		_hp -= damage;
		_attacked = true;
		timeAttacked.start();
	}
	if (_hp <= 0)
	{
		setAnimationDie();
		timeHide.start();
		_death = true;
	}
}

void DynamicObject::reset()
{
	if (!_isReset && !resetBound.intersectsWith(*viewPortGlobal))//reset
	{
		_isReset = true;
		_hp = initHP;
		_death = false;
		visible = true;
		x = initX;
		y = initY;
		toLeft = initToLeft;
		for (auto it = _weapons.begin(); it != _weapons.end();)
		{
			delete it[0];
			it = _weapons.erase(it);
		}
	}
}

vector<Weapon*>* DynamicObject::getWeapons()
{
	return &_weapons;
}



