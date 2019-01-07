#include "BusterShot.h"

void BusterShot::loadResources()
{
	_animations[bullet_lv1] = animationsGlobal->get(bullet_lv1);
}

BusterShot::BusterShot(float x, float y,bool toLeft)
{
	this->x = x;
	this->y = y;
	this->toLeft = toLeft;
	this->speed.vx = toLeft ? -0.25f : 0.25f;
	this->speed.vy = 0.00f;
	_damage = 1;
	loadResources();
	soundsGlobal->play(sound_bul_lv1);
}

BusterShot::~BusterShot()
{
	if (_isCollision)
		_weaponEffect->createBusterEffect(x, y, toLeft);
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
void BusterShot::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	this->dt = dt;
	speed.vx += toLeft ? -0.001f * dt :  0.001f * dt;
	dx = speed.vx * dt;
	this->x += dx;
}