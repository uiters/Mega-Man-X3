#include "HeadGunnerBullet.h"


HeadGunnerBullet::HeadGunnerBullet(float x, float y, bool nx, bool ny)
{
	this->x = x;
	this->y = y;
	this->nx = nx;
	this->ny = ny;
}

HeadGunnerBullet::HeadGunnerBullet(int id, float x, float y, bool nx, bool ny)
{
	this->_id = id;
	this->x = x;
	this->y = y;
	this->nx = nx;
	this->ny = ny;
}

HeadGunnerBullet::~HeadGunnerBullet()
{
}

void HeadGunnerBullet::update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects)
{
	GameObject::update(dt);

	speed.vy += HEAD_GUNNER_BULLET_GRAVITY;

	if (nx == false) speed.vx = -abs(speed.vx);
	if (nx == true) speed.vx = abs(speed.vx);

	collisionStatic(staticObjects);
}

void HeadGunnerBullet::render(DWORD dt, D3DCOLOR colorBrush)
{
	auto center = cameraGlobal->transform(x, y);
	_animations[state]->render(center.x, center.y);
}

void HeadGunnerBullet::setState(int state)
{
	speed.vx = HEAD_GUNNER_BULLET_SPEED_X;
	speed.vy = HEAD_GUNNER_BULLET_SPEED_Y;

	this->state = state;
	_animations[state]->reset();
}

void HeadGunnerBullet::loadResources()
{
	CTextures * textures = CTextures::getInstance();

	if (textures->getTexture(HEAD_GUNNER_BULLET_ID_TEXTURE) == NULL)
		textures->add(HEAD_GUNNER_BULLET_ID_TEXTURE, L"Resource\\Textures\\HeadeGunnerBullets.png", 0, 0, D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();

	LPANIMATION ani;

	// default
	sprites->addSprite(10001, HEAD_GUNNER_BULLET_ID_TEXTURE, 77, 11, 7, 7);

	ani = new CAnimation(200);
	ani->add(10001);
	animations->add(HEAD_GUNNER_BULLET_STATE_DEFAULT, ani);

	// add animations
	this->addAnimation(HEAD_GUNNER_BULLET_STATE_DEFAULT);
}

void HeadGunnerBullet::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void HeadGunnerBullet::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 8;
	bottom = y + 8;
}

void HeadGunnerBullet::collisionStatic(unordered_map<int, CTreeObject*>* staticObjects)
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
