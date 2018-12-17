#include "NotorBangerBullet.h"


NotorBangerBullet::NotorBangerBullet(float x, float y, bool nx, bool ny, int distance)
{
	this->x = x;
	this->y = y;
	this->nx = nx;
	this->ny = ny;
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
	this->isDelete = false;
	this->distance = distance;
}

NotorBangerBullet::~NotorBangerBullet()
{
}

void NotorBangerBullet::update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects)
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
	CTextures * textures = CTextures::getInstance();

	if (textures->getTexture(NOTOR_BANGER_BULLET_ID_TEXTURE) == NULL)
		textures->add(NOTOR_BANGER_BULLET_ID_TEXTURE, L"Resource\\Textures\\enemies.png", 0, 0, D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();

	LPANIMATION ani;

	// default
	sprites->addSprite(10001, NOTOR_BANGER_BULLET_ID_TEXTURE, 188, 66, 8, 8); // 8 x 8

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

void NotorBangerBullet::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 8;
	bottom = y + 8;
}

void NotorBangerBullet::collisionStatic(unordered_map<int, CTreeObject*>* staticObjects)
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
