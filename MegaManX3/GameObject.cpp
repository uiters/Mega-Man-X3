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
bool GameObject::collisionGameObject(GameObject* obj1, GameObject* obj2)
{
	auto e = collision->sweptAABBEx(dt, obj1, obj2);
	if (e->t > 0 && e->t <= 1.0f)
	{
		delete e;
		return true;
	}
	delete e;
	return false;
}

bool GameObject::collisionBullet(GameObject* bullet1, GameObject* obj2)
{
	auto e = Collision::getInstance()->sweptAABBEx(dt, bullet1, obj2);
	if (e->t > 0 && e->t <= 1.0f)
	{
		delete e;
		return true;
	}
	delete e;
	return false;
}
GameObject::~GameObject()
{

}
