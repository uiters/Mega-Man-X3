#pragma once
#include "GameObject.h"
class Megaman : public GameObject
{
public:
	Megaman() : GameObject(0, 0, 0, 20, 20) {}
	~Megaman();
};

