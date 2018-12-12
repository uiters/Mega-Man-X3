#include "Helit.h"


void Helit::loadResources()
{

}
Helit::Helit()
{

}

Helit::Helit(int id, float x, float y, bool toLeft)
{
	this->_idObject = id;
	this->x = x;
	this->y = y;
	this->toLeft = toLeft;
}

void Helit::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	//right = x 
}

Helit * Helit::clone(int id, int x, int y)
{
	auto helit = new Helit();
	helit->x = x;
	helit->y = y;
	helit->_animations = this->_animations;//copy animation
	return helit;
}

Helit::~Helit()
{
}
