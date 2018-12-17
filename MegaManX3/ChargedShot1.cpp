#include "ChargedShot1.h"

void ChargedShot1::loadResources()
{
	spritesGlobal->add(bullet_lv2, Megaman, 26, 373, 39, 386);
	spritesGlobal->add(bullet_lv2 + 1, Megaman, 48, 368, 71, 391);
	spritesGlobal->add(bullet_lv2 + 2, Megaman, 82, 375, 109, 386);
	spritesGlobal->add(bullet_lv2 + 3, Megaman, 120, 376, 151, 383);
	spritesGlobal->add(bullet_lv2 + 4, Megaman, 163, 374, 200, 385);
	spritesGlobal->add(bullet_lv2 + 5, Megaman, 216, 368, 255, 386);
	spritesGlobal->add(bullet_lv2 + 6, Megaman, 265, 368, 300, 389);
	auto ani = new CAnimation(900);
	ani->add(bullet_lv2 + 0, 20);
	ani->add(bullet_lv2 + 1, 30);
	ani->add(bullet_lv2 + 2, 60);
	ani->add(bullet_lv2 + 3, 70);
	ani->add(bullet_lv2 + 4, 130);
	ani->add(bullet_lv2 + 5, 500);
	ani->add(bullet_lv2 + 6, 100);
	animationsGlobal->add(bullet_lv2, ani);
	_animations[bullet_lv2] = ani;
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
}

ChargedShot1::~ChargedShot1()
{
	delete _animations[bullet_lv2];
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
void ChargedShot1::update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects)
{
	this->dt = dt;
	dx = speed.vx * dt;
	this->x += dx;
}