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
	loadResources();
}

BusterShot::~BusterShot()
{
	delete _animations[bullet_lv1];
}

void BusterShot::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
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
