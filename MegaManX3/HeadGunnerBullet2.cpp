#include "HeadGunnerBullet2.h"


HeadGunnerBullet2::HeadGunnerBullet2(float x, float y, bool nx, bool ny)
{
	this->x = x;
	this->y = y;
	this->nx = nx;
	this->ny = ny;
	loadResources();
	setState(bullet_head_gun_state_2);
	if (nx) speed.vx = abs(speed.vx); // right
	else speed.vx = -abs(speed.vx);
}

HeadGunnerBullet2::~HeadGunnerBullet2()
{
	timeDelaySmoke.start();
}

void HeadGunnerBullet2::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	timeDelaySmoke.update();

	GameObject::update(dt);

	if (timeDelaySmoke.isStop())
	{
		if (nx) //left
		{
			_weaponEffect->createBulletSmoke(x, y + 3);
		}
		else //right
		{
			_weaponEffect->createBulletSmoke(x + 21, y + 3);
		}

		timeDelaySmoke.start();
	}
	collisionStatic(staticObjects);
}

void HeadGunnerBullet2::render(DWORD dt, D3DCOLOR colorBrush)
{
	auto center = cameraGlobal->transform(x, y);
	if(nx)
		_animations[state]->renderFlipX(center.x, center.y);
	else
		_animations[state]->render(center.x, center.y);
}

void HeadGunnerBullet2::setState(int state)
{
	speed.vx = HEAD_GUNNER_BULLET2_SPEED_X;
	speed.vy = HEAD_GUNNER_BULLET2_SPEED_Y;

	this->state = state;
	_animations[state]->reset();
}

void HeadGunnerBullet2::loadResources()
{
	_animations[bullet_head_gun_state_2] = animationsGlobal->get(bullet_head_gun_state_2);
}

void HeadGunnerBullet2::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void HeadGunnerBullet2::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 8;
	bottom = y + 8;
}

void HeadGunnerBullet2::collisionStatic(unordered_map<int, GameObject*>* staticObjects)
{
	vector<CollisionEvent*> coEvents;
	vector<CollisionEvent*> coEventsResult;

	collision->findCollisions(dt, this, *staticObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		collision->filterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 1.f;
		y += min_ty * dy + ny * 1.f;

		isDelete = true;
	}
	UINT size = coEvents.size();
	for (UINT i = 0; i < size; ++i) delete coEvents[i];
}
