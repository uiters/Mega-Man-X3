#include "HeadGunner.h"


HeadGunner::HeadGunner(UINT id, float x, float y, bool nx) : DynamicObject(id, x, y, 0, 0)
{
	initDamage = 4.0f;
	this->nx = nx;
	this->initToLeft = !nx;
	this->repeat = 0;

	initHP = _hp = 4;
	setResetBound();
}

HeadGunner::~HeadGunner()
{
}

void HeadGunner::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	this->dt = dt;
	updateWeapon(dt, staticObjects);

	if (!visible) return;
	if (_death) {
		calculateDie();
	}
	else
	{
		GameObject::update(dt);

		if (_animations[state]->isLastFrame()) {
			if (state == 100 || state == 200)
				createBullet2();


			if (state == 300 || state == 400)
				createBullet();

			if (state == 300) {
				if (repeat > 0) {
					repeat = 0;
					state += 100;
				}
				else repeat++;
			}
			else state += 100;

			if (state > 400) state = 0;
			setState(state);
		}
	}
}

void HeadGunner::updateWeapon(DWORD dt, unordered_map<int, GameObject*>* staticObjects)
{
	for (auto bullet = _weapons.begin(); bullet != _weapons.end();)
	{
		bullet[0]->update(dt, staticObjects);

		if (bullet[0]->getIsDelete())
		{
			int x = bullet[0]->x - 16;
			int y = bullet[0]->y - 20;
			collisionEffect->createEffect(x, y);
			delete bullet[0];
			bullet = _weapons.erase(bullet);
		}
		else ++bullet;
	}
}

void HeadGunner::render(DWORD dt, D3DCOLOR colorBrush)
{
	collisionEffect->render(dt, false);
	renderWeapon(dt, colorBrush);

	if (!visible) return;

	if (_death) {
		renderDie(dt);
		timeHide.update();

		if (timeHide.isStop())
			visible = false;
	}
	else
	{
		renderNormal(dt);
	}

}

void HeadGunner::renderDie(DWORD dt, D3DCOLOR colorBrush)
{
	for (int i = 0; i < 4; ++i) {
		auto center = cameraGlobal->transform(die[i].x, die[i].y);
		_animations[HEAD_GUNNER_STATE_DIE + i]->render(center.x, center.y, 0, this->showColor ? WHITE(100) : WHITE(255));
	}
	if (++timeSwitchColor == 2)
		showColor = !showColor, timeSwitchColor = 0;
}

void HeadGunner::renderNormal(DWORD dt, D3DCOLOR colorBrush)
{
	if (_attacked)
	{
		timeAttacked.update();
		if (timeAttacked.isStop())
		{
			_attacked = false;
		}
		else colorBrush = LIGHTCYAN(128);
	}
	auto center = cameraGlobal->transform(x, y);
	if (nx != true) _animations[state]->render(center.x, center.y, false, colorBrush);
	else _animations[state]->renderFlipX(center.x, center.y, false, colorBrush);
	shotEffect->render(dt, true);
}

void HeadGunner::calculateDie()
{
	speed.vy += 0.00115f * dt;
	speed.vx += 0.000125 *dt;

	dx = speed.vx * dt;
	dy = speed.vy * dt;

	die[0].x += dx;
	die[1].x += dx * 0.75;
	die[2].x -= dx;
	die[3].x -= dx * 1.25;

	die[0].y += dy * 2;
	die[1].y += dy * 0.5;
	die[2].y += dy * 1.5;
	die[3].y += dy;
}

void HeadGunner::setState(int state)
{
	this->state = state;
	_animations[state]->reset();
}

void HeadGunner::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 41;
	bottom = y + 45;
}

void HeadGunner::loadResources()
{
	CTextures * textures = CTextures::getInstance();
	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();
	LPANIMATION ani;

	if (textures->getTexture(HEAD_GUNNER_ID_TEXTURE)) goto LoadAni;

	textures->add(HEAD_GUNNER_ID_TEXTURE, L"Resource\\Textures\\enemies.png", 0, 0, D3DCOLOR_XRGB(255, 0, 255));

	// default
	sprites->addSprite(20001, HEAD_GUNNER_ID_TEXTURE, 4, 334, 41, 45);// 41 x 45
	// shot top
	sprites->addSprite(20011, HEAD_GUNNER_ID_TEXTURE, 45, 334, 41, 45);// 41 x 45
	sprites->addSprite(20012, HEAD_GUNNER_ID_TEXTURE, 87, 334, 41, 45);
	sprites->addSprite(20013, HEAD_GUNNER_ID_TEXTURE, 128, 334, 41, 45);
	sprites->addSprite(20014, HEAD_GUNNER_ID_TEXTURE, 4, 334, 41, 45);
	// shot bottom
	sprites->addSprite(20021, HEAD_GUNNER_ID_TEXTURE, 5, 389, 41, 45);// 41 x 45
	sprites->addSprite(20022, HEAD_GUNNER_ID_TEXTURE, 48, 389, 41, 45);
	sprites->addSprite(20023, HEAD_GUNNER_ID_TEXTURE, 89, 388, 41, 45);
	sprites->addSprite(20024, HEAD_GUNNER_ID_TEXTURE, 4, 334, 41, 45);
	// shot left
	sprites->addSprite(20031, HEAD_GUNNER_ID_TEXTURE, 4, 334, 41, 45);
	// shot right
	sprites->addSprite(20041, HEAD_GUNNER_ID_TEXTURE, 4, 334, 41, 45);
	// die
	sprites->addSprite(20051, HEAD_GUNNER_ID_TEXTURE, 177, 353, 15, 16);
	sprites->addSprite(20052, HEAD_GUNNER_ID_TEXTURE, 195, 353, 8, 12);
	sprites->addSprite(20053, HEAD_GUNNER_ID_TEXTURE, 209, 357, 19, 8);
	sprites->addSprite(20054, HEAD_GUNNER_ID_TEXTURE, 208, 368, 7, 13);

LoadAni:

	ani = new CAnimation(2000);
	ani->add(20001);
	animations->add(HEAD_GUNNER_STATE_DEFAULT, ani);



	ani = new CAnimation(200);
	ani->add(20011);
	ani->add(20012);
	ani->add(20013);
	ani->add(20014);
	animations->add(HEAD_GUNNER_STATE_SHOT_TOP, ani);



	ani = new CAnimation(200);
	ani->add(20021);
	ani->add(20022);
	ani->add(20023);
	ani->add(20024);
	animations->add(HEAD_GUNNER_STATE_SHOT_BOTTOM, ani);



	ani = new CAnimation(1000);
	ani->add(20031);
	animations->add(HEAD_GUNNER_STATE_SHOT_LEFT, ani);



	ani = new CAnimation(1000);
	ani->add(20041);
	animations->add(HEAD_GUNNER_STATE_SHOT_RIGHT, ani);



	for (int i = 0; i < 4; i++)
	{
		ani = new CAnimation(100);
		ani->add(20051 + i);
		animations->add(HEAD_GUNNER_STATE_DIE + i, ani);
		this->addAnimation(HEAD_GUNNER_STATE_DIE + i);
	}

	// add animations
	this->addAnimation(HEAD_GUNNER_STATE_DEFAULT);
	this->addAnimation(HEAD_GUNNER_STATE_SHOT_TOP);
	this->addAnimation(HEAD_GUNNER_STATE_SHOT_BOTTOM);
	this->addAnimation(HEAD_GUNNER_STATE_SHOT_LEFT);
	this->addAnimation(HEAD_GUNNER_STATE_SHOT_RIGHT);
}

void HeadGunner::createExplosion(float x, float y)
{
	collisionEffect->createEffect(x, y);
}

void HeadGunner::setAnimationDie()
{
	die[0] = die[1] = die[2] = die[3] = { x, y };
	speed.vy = -0.0195f *dt;
	speed.vx = 0.0032f * dt;
	collisionEffect->createEffect(x, y);
	timeHide.start();
}

void HeadGunner::setResetBound()
{
	resetBound.x = x;
	resetBound.y = y;
	resetBound.width = 40;
	resetBound.height = 48;
}

void HeadGunner::createBullet()
{
	int x, y;

	if (nx)
	{
		if (state == 300) {
			x = this->x + 10 + 5;
			y = this->y;
		}
		else if (state == 400) {
			x = this->x + 18 + 5;
			y = this->y;
		}
	}
	else
	{
		if (state == 300) {
			x = this->x + 18 - 1;
			y = this->y;
		}
		else if (state == 400) {
			x = this->x + 10 - 1;
			y = this->y;
		}
	}

	shotEffect->createEffect(x + 5, y);

	HeadGunnerBullet* bullet = new HeadGunnerBullet(
		x,
		y,
		this->nx,
		true
	);

	_weapons.emplace_back(bullet);

}

void HeadGunner::createBullet2()
{
	int x, y;

	if (nx)
	{
		if (state == 100) {
			x = this->x + 20;
			y = this->y + 9;
		}
		else if (state == 200) {
			x = this->x + 24;
			y = this->y + 13;
		}
	}
	else
	{
		if (state == 100) {
			x = this->x - 4;
			y = this->y + 9;
		}
		else if (state == 200) {
			x = this->x;
			y = this->y + 13;
		}
	}
	if(nx)
		shotEffect->createEffect(x + 10, y + 2);
	else shotEffect->createEffect(x + 10, y + 2);

	HeadGunnerBullet2* bullet2 = new HeadGunnerBullet2(
		x,
		y,
		this->nx,
		true
	);

	_weapons.emplace_back(bullet2);
}