#pragma once
#include "GameObject.h"
#include "Camera.h"
class Weapon :
	public GameObject
{
private:
	int _damage = 0;
public:
	Weapon();
	~Weapon();
};

