#include "StaticObject.h"

StaticObject::StaticObject(UINT id, float x, float y, int width, int height)
{
	this->_id = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

bool StaticObject::canBreak()
{
	return _canBreak;
}


void StaticObject::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + width;
}