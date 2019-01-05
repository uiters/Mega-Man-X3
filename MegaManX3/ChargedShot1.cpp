#include "ChargedShot1.h"

void ChargedShot1::loadResources()
{

	_animations[bullet_lv2] = animationsGlobal->get(bullet_lv2);
	_animations[bullet_lv2]->reset();
}

ChargedShot1::ChargedShot1(float x, float y, bool toLeft)
{
	loadResources();
	this->x = x;
	this->y = y;
	this->speed.vx = toLeft ? -0.325f : 0.325f;
	this->speed.vy = 0.00f;
	dy = 0;
	this->toLeft = toLeft;
	_damage = 2;
	soundsGlobal->play(sound_bul_lv2);
}

ChargedShot1::~ChargedShot1()
{
	if (_isCollision)
		_weaponEffect->createCharged1Effect(x, y, toLeft);
}

void ChargedShot1::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (toLeft)
	{
		left = x + 10.f;
		top = y - 6.f;

		right = x + 14.f;
		bottom = y + 6.f;
	}
	else
	{
		left = x - 10.f;
		top = y - 6.f;
		right = x + 10.f;
		bottom = y + 6.f;
	}

}

void ChargedShot1::render(DWORD dt, D3DCOLOR colorBrush)
{
	auto pos = cameraGlobal->transform(x, y);
	if (toLeft)
		_animations[bullet_lv2]->renderFlipX(pos.x - 10.f, pos.y, true, colorBrush);
	else _animations[bullet_lv2]->render(pos.x, pos.y, true, colorBrush);
}
void ChargedShot1::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	this->dt = dt;
	speed.vx += toLeft ? -0.001f * dt : 0.001f * dt;
	dx = speed.vx * dt;
	this->x += dx;
}