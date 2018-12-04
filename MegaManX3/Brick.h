#pragma once
#include "StaticObject.h"
class Brick
	:public StaticObject
{
public:

	Brick(UINT id, int x, int y, int right, int bottom);
	~Brick();
};

