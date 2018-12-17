#include "BusterShot.h"

void BusterShot::loadResources()
{
	spritesGlobal->add(bullet_lv1, Megaman, 5, 377, 12, 382);
	auto ani = new CAnimation(50);
	ani->add(bullet_lv1);
	animationsGlobal->add(bullet_lv1, ani);
	_animations[bullet_lv1] = ani;
}

BusterShot::BusterShot(float x, float y,bool toLeft)
{
	this->x = x;
	this->y = y;
	this->toLeft = toLeft;
	this->speed.vx = toLeft ? -0.25f : 0.25f;
	this->speed.vy = 0.00f;
	loadResources();
}

BusterShot::~BusterShot()
{
	delete _animations[bullet_lv1];
}

void BusterShot::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x - 4;
	top = y - 6;
	right = x + 8;
	bottom = y + 6;
}

void BusterShot::render(DWORD dt, D3DCOLOR colorBrush)
{
	auto pos = cameraGlobal->transform(x, y);
	if (toLeft)
		_animations[bullet_lv1]->renderFlipX(pos.x, pos.y, true, colorBrush);
	else _animations[bullet_lv1]->render(pos.x, pos.y, true, colorBrush);
}
void BusterShot::update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects)
{
	this->dt = dt;
	dx = speed.vx * dt;
	this->x += dx;
}