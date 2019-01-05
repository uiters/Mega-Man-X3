#include "HelitBullet.h"

void HelitBullet::loadResources()
{
	auto ani = new CAnimation(100);
	ani->add(HelitBulletAnimation);
	_animations[HelitBulletAnimation] = ani;
}


HelitBullet::HelitBullet(int x, int y, bool toLeft)
{
	loadResources();
	this->x = x;
	this->y = y;
	this->speed.vx = toLeft ? -0.125f : 0.125f;
	this->speed.vy = 0.00f;
	this->toLeft = toLeft;
	_damage = 1;
}

HelitBullet::~HelitBullet()
{
	delete _animations[HelitBulletAnimation];
}

void HelitBullet::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 15;
	bottom = y + 10;
}

void HelitBullet::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	this->dt = dt;
	dx = speed.vx * dt;
	this->x += dx;
}

void HelitBullet::render(DWORD dt, D3DCOLOR colorBrush)
{
	auto pos = cameraGlobal->transform(x, y);
	if (toLeft)
		_animations[HelitBulletAnimation]->render(pos.x, pos.y);
	else _animations[HelitBulletAnimation]->renderFlipX(pos.x, pos.y);
}
