#pragma once
#include "StaticObject.h"
class Block :
	public StaticObject
{
public:
	Block(UINT id, int x, int y, int width, int height);
	~Block();
};

