#include "Brick.h"

Brick::Brick(UINT id, int x, int y, int width, int height)
{
	this->_id = id;
	this->box.x = x;
	this->box.y = y;
	this->box.width = width;
	this->box.height = height;
	this->x = x;
	this->y = y;
}

Brick::~Brick()
{
}
