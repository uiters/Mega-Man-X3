#pragma once
#include "GameObject.h"
#include "Camera.h"
class Weapon :
	public GameObject
{
protected:
	int _damage = 0;
	bool isDelete;
public:
	Weapon();
	~Weapon();
	virtual bool getIsDelete() { return isDelete; };
	virtual int getDamage() { return _damage; };
};

