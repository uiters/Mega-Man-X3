#include "GameObject.h"

Collision* GameObject::collision = Collision::getInstance();

GameObject::GameObject(UINT id, float x, float y, float vx, float vy) :speed( vx , vy ) {
	this->x = x;
	this->y = y;
	this->_id = id;
}



void GameObject::addAnimation(UINT animationId)
{
	LPANIMATION ani = animationsGlobal->get(animationId);
	_animations[animationId] = ani;
}



CRectangle GameObject::getBoundBox()
{
	float left, top, right, bottom;
	this->getBoundingBox(left, top, right, bottom);
	return CRectangle::fromLTRB(left, top, right, bottom);
}

void GameObject::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	this->dt = dt;
	dx = speed.vx * dt;
	dy = speed.vy * dt;
}

GameObject::~GameObject()
{

}
