#include "HeadGunner.h"

HeadGunner::HeadGunner()
{
	this->x = 10;
	this->y = 100;
	this->nx = true;
}

HeadGunner::HeadGunner(int id, float x, float y, bool nx)
{
	this->_id = id;
	this->x = x;
	this->y = y;
	this->nx = nx;
}

HeadGunner::~HeadGunner()
{
}

void HeadGunner::update(DWORD dt, vector<LPObject>* coObjects)
{
	GameObject::update(dt);

	if (_animations[state]->isLastFrame()) {
		state += 100;
		if (state > 400) state = 0;
		setState(state);
	}
}

void HeadGunner::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (nx != true) _animations[state]->render(x, y, false);
	else _animations[state]->renderFlipX(x, y);
}

void HeadGunner::setState(int state)
{
	this->state = state;
	_animations[state]->reset();
}

void HeadGunner::loadResources()
{
	CTextures * textures = CTextures::getInstance();

	textures->add(HEAD_GUNNER_ID_TEXTURE, L"enemies.png", 0, 0, D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();

	LPANIMATION ani;

	// default
	sprites->addSprite(20001, HEAD_GUNNER_ID_TEXTURE, 4, 334, 41, 45);// 41 x 45
	
	ani = new CAnimation(100);
	ani->add(20001);
	animations->add(HEAD_GUNNER_STATE_DEFAULT, ani);

	// shot top
	sprites->addSprite(20011, HEAD_GUNNER_ID_TEXTURE, 45, 334, 41, 45);// 41 x 45
	sprites->addSprite(20012, HEAD_GUNNER_ID_TEXTURE, 87, 334, 41, 45);
	sprites->addSprite(20013, HEAD_GUNNER_ID_TEXTURE, 128, 334, 41, 45);
	sprites->addSprite(20014, HEAD_GUNNER_ID_TEXTURE, 4, 334, 41, 45);

	ani = new CAnimation(500);
	ani->add(20011);
	ani->add(20012);
	ani->add(20013);
	ani->add(20014);
	animations->add(HEAD_GUNNER_STATE_SHOT_TOP, ani);

	// shot bottom
	sprites->addSprite(20021, HEAD_GUNNER_ID_TEXTURE, 5, 389, 41, 45);// 41 x 45
	sprites->addSprite(20022, HEAD_GUNNER_ID_TEXTURE, 48, 389, 41, 45);
	sprites->addSprite(20023, HEAD_GUNNER_ID_TEXTURE, 89, 388, 41, 45);
	sprites->addSprite(20024, HEAD_GUNNER_ID_TEXTURE, 4, 334, 41, 45);

	ani = new CAnimation(500);
	ani->add(20021);
	ani->add(20022);
	ani->add(20023);
	ani->add(20024);
	animations->add(HEAD_GUNNER_STATE_SHOT_BOTTOM, ani);

	// shot left
	sprites->addSprite(20031, HEAD_GUNNER_ID_TEXTURE, 4, 334, 41, 45);

	ani = new CAnimation(1000);
	ani->add(20031);
	animations->add(HEAD_GUNNER_STATE_SHOT_LEFT, ani);

	// shot right
	sprites->addSprite(20041, HEAD_GUNNER_ID_TEXTURE, 4, 334, 41, 45);

	ani = new CAnimation(1000);
	ani->add(20041);
	animations->add(HEAD_GUNNER_STATE_SHOT_RIGHT, ani);

	// die
	sprites->addSprite(20051, HEAD_GUNNER_ID_TEXTURE, 177, 353, 15, 16);
	sprites->addSprite(20052, HEAD_GUNNER_ID_TEXTURE, 195, 353, 8, 12);
	sprites->addSprite(20053, HEAD_GUNNER_ID_TEXTURE, 209, 357, 19, 8);
	sprites->addSprite(20054, HEAD_GUNNER_ID_TEXTURE, 208, 368, 7, 13);

	ani = new CAnimation(100);
	ani->add(20051);
	ani->add(20052);
	ani->add(20053);
	ani->add(20054);
	animations->add(HEAD_GUNNER_STATE_DIE, ani);

	// add animations
	this->addAnimation(HEAD_GUNNER_STATE_DEFAULT);
	this->addAnimation(HEAD_GUNNER_STATE_SHOT_TOP);
	this->addAnimation(HEAD_GUNNER_STATE_SHOT_BOTTOM);
	this->addAnimation(HEAD_GUNNER_STATE_SHOT_LEFT);
	this->addAnimation(HEAD_GUNNER_STATE_SHOT_RIGHT);
	this->addAnimation(HEAD_GUNNER_STATE_DIE);
}
