#include "HeadGunner.h"


HeadGunner::HeadGunner(int id, float x, float y, bool nx)
{
	this->_id = id;
	this->x = x;
	this->y = y;
	this->nx = nx;
	this->repeat = 0;
	this->initX = x;
	this->initY = y;


	_death = false;
	_hp = 5;
}

HeadGunner::~HeadGunner()
{
}

void HeadGunner::update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects)
{
	this->dt = dt;
	if (_death) {
		calculateDie();
		return;
	}

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

void HeadGunner::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (_death) {
		renderDie(dt);
		collisionEffect->render(dt, false);
		return;
	}

	auto center = cameraGlobal->transform(x, y);
	if (nx != true) _animations[state]->render(center.x, center.y);
	else _animations[state]->renderFlipX(center.x, center.y);

	int size = _weapons.size();
	for (int i = 0; i < size; ++i)
	{
		_weapons[i]->render(dt);
	}

	shotEffect->render(dt, true);
	collisionEffect->render(dt, false);
}

void HeadGunner::renderDie(DWORD dt, D3DCOLOR colorBrush)
{
	for (int i = 0; i < 4; i++) {
		auto center = cameraGlobal->transform(die[i].x, die[i].y);
		_animations[HEAD_GUNNER_STATE_DIE + i]->render(center.x, center.y);
	}
}

void HeadGunner::calculateDie()
{
	speed.vy += 0.00115f * dt;
	speed.vx += 0.000125 *dt;

	dx = speed.vx * dt;
	dy = speed.vy * dt;

	die[0].x += dx;
	die[1].x += dx * 2;
	die[2].x -= dx;
	die[3].x -= dx * 2;

	die[0].y += dy;
	die[1].y += dy;
	die[2].y += dy;
	die[3].y += dy;
}

void HeadGunner::setState(int state)
{
	this->state = state;
	_animations[state]->reset();
}

HeadGunner * HeadGunner::clone(int id, int x, int y)
{
	return nullptr;
}

void HeadGunner::resetPosition()
{
	this->x = this->initX;
	this->y = this->initY;
}

void HeadGunner::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 40;
	bottom = y + 48;
}

void HeadGunner::loadResources()
{
	CTextures * textures = CTextures::getInstance();
	if(!textures->getTexture(HEAD_GUNNER_ID_TEXTURE))
		textures->add(HEAD_GUNNER_ID_TEXTURE, L"Resource\\Textures\\enemies.png", 0, 0, D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();

	LPANIMATION ani;

	// default
	sprites->addSprite(20001, HEAD_GUNNER_ID_TEXTURE, 4, 334, 41, 45);// 41 x 45
	
	ani = new CAnimation(2000);
	ani->add(20001);
	animations->add(HEAD_GUNNER_STATE_DEFAULT, ani);

	// shot top
	sprites->addSprite(20011, HEAD_GUNNER_ID_TEXTURE, 45, 334, 41, 45);// 41 x 45
	sprites->addSprite(20012, HEAD_GUNNER_ID_TEXTURE, 87, 334, 41, 45);
	sprites->addSprite(20013, HEAD_GUNNER_ID_TEXTURE, 128, 334, 41, 45);
	sprites->addSprite(20014, HEAD_GUNNER_ID_TEXTURE, 4, 334, 41, 45);

	ani = new CAnimation(200);
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

	ani = new CAnimation(200);
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
	bullet->loadResources();
	bullet->setState(HEAD_GUNNER_BULLET_STATE_DEFAULT);

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
	bullet2->loadResources();
	bullet2->setState(HEAD_GUNNER_BULLET2_STATE_DEFAULT);

	_weapons.emplace_back(bullet2);
}
