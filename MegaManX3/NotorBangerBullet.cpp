#include "NotorBangerBullet.h"



NotorBangerBullet::NotorBangerBullet()
{
	this->x = 50;
	this->y = 100;
	this->nx = true;
	this->ny = false;
	this->limit = 100 + 48;
	this->isDelete = false;
}

NotorBangerBullet::NotorBangerBullet(float x, float y, bool nx, bool ny, int distance)
{
	this->x = x;
	this->y = y;
	this->nx = nx;
	this->ny = ny;
	this->limit = y + 48;
	this->isDelete = false;
	this->distance = distance;
}

NotorBangerBullet::NotorBangerBullet(int id, float x, float y, bool nx, bool ny, int distance)
{
	this->_id = id;
	this->x = x;
	this->y = y;
	this->nx = nx;
	this->ny = ny;
	this->limit = y + 48;
	this->isDelete = false;
	this->distance = distance;
}

NotorBangerBullet::~NotorBangerBullet()
{
}

void NotorBangerBullet::update(DWORD dt, vector<LPObject>* coObjects)
{
	GameObject::update(dt);

	speed.vy += NOTOR_BANGER_BULLET_GRAVITY;
	x += dx;
	y += dy;

	if (nx == false) speed.vx = -abs(speed.vx);
	if (nx == true) speed.vx = abs(speed.vx);

	if (y >= limit) {
		y = limit;
		isDelete = true;
	}
}

void NotorBangerBullet::render(DWORD dt, D3DCOLOR colorBrush)
{
	/*if (ny == true) _animations[state]->render(x, y);
	else _animations[state]->renderFlipY(x, y);*/
	_animations[state]->render(x, y);
}

void NotorBangerBullet::setState(int state)
{	
	switch (distance)
	{
	case 0:
		speed.vx = NOTOR_BANGER_BULLET_SPEED_X_SMALL;
		speed.vy = -NOTOR_BANGER_BULLET_SPEED_Y_SMALL;
		break;
	case 1:
		speed.vx = NOTOR_BANGER_BULLET_SPEED_X_MEDIUM;
		speed.vy = -NOTOR_BANGER_BULLET_SPEED_Y_MEDIUM;
		break;
	case 2:
		speed.vx = NOTOR_BANGER_BULLET_SPEED_X_LARGE;
		speed.vy = -NOTOR_BANGER_BULLET_SPEED_Y_LARGE;
		break;
	default:
		break;
	}

	this->state = state;
	_animations[state]->reset();
}

void NotorBangerBullet::loadResources()
{
	CTextures * textures = CTextures::getInstance();

	textures->add(NOTOR_BANGER_BULLET_ID_TEXTURE, L"enemies.png", 0, 0, D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();

	LPANIMATION ani;

	// default
	sprites->addSprite(10001, NOTOR_BANGER_BULLET_ID_TEXTURE, 188, 66, 8, 8); // 48 x 48

	ani = new CAnimation(200);
	ani->add(10001);
	animations->add(NOTOR_BANGER_BULLET_STATE_DEFAULT, ani);

	// add animations
	this->addAnimation(NOTOR_BANGER_BULLET_STATE_DEFAULT);
}

void NotorBangerBullet::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}
