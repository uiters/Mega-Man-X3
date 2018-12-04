#include "Brick.h"






Brick::Brick(UINT id, int x, int y, int right, int bottom)
{
	this->_id = id;
	this->box.x = x;
	this->box.y = y;
	this->box.width = right - x;
	this->box.height = bottom - y;
	this->x = x;
	this->y = y;
}

Brick::~Brick()
{
}
