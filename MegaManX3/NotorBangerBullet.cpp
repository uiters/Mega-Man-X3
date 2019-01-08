#include "NotorBangerBullet.h"


NotorBangerBullet::NotorBangerBullet(float x, float y, bool nx, bool ny, int distance)
{
	this->x = x;
	this->y = y;
	this->nx = nx;
	this->ny = ny;
	this->isDelete = false;
	this->distance = distance;
	loadResources();
	setState(bullet_head_gun_state_default);
	_damage = 2;
}


NotorBangerBullet::~NotorBangerBullet()
{
}

void NotorBangerBullet::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	GameObject::update(dt);

	speed.vy += NOTOR_BANGER_BULLET_GRAVITY;

	if (nx == false) speed.vx = -abs(speed.vx);
	if (nx == true) speed.vx = abs(speed.vx);

	collisionStatic(staticObjects);
}

void NotorBangerBullet::render(DWORD dt, D3DCOLOR colorBrush)
{
	auto center = cameraGlobal->transform(x, y);
	_animations[state]->render(center.x, center.y);
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
	_animations[bullet_head_gun_state_default] = animationsGlobal->get(bullet_head_gun_state_default);
}

void NotorBangerBullet::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void NotorBangerBullet::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 8;
	bottom = y + 8;
}

void NotorBangerBullet::collisionStatic(unordered_map<int, GameObject*>* staticObjects)
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
