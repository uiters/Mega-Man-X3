#include "ITemHP.h"
#include "Camera.h"

ITemHP::ITemHP(float x, float y, bool isBig)
{
	ani = new AnimationOneTime(100);
	this->x = x;
	this->y = y;
	if (isBig) {
		ani->add(ItemBig);
		ani->add(ItemBig + 1, 500);
		ani->add(ItemBig + 2, 500);
		ani->add(ItemBig + 3, 2000);
		initHP = 5;
		width = 16;
		height = 12;
	}
	else
	{
		ani->add(ItemSmall);
		ani->add(ItemSmall + 1, 1500);
		ani->add(ItemSmall + 2, 1500);
		ani->add(ItemSmall + 3, 2000);
		initHP = 2;
		width = 10;
		height = 8;
	}
	visible = true;
}

void ITemHP::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	if (visible)
	{
		GameObject::update(dt);
		speed.vy += 0.0005 * dt;
		if (!isStand)
			checkCollisionStatic(staticObjects); //fall

		if (this->getBoundBox().intersectsWith(mainGlobal->getBoundBox()) ||
			mainGlobal->collisionGameObject(this, mainGlobal))
		{
			mainGlobal->addHP(initHP);
			visible = false;
		}
	}
}

void ITemHP::checkCollisionStatic(unordered_map<int, GameObject*>* staticObjects)
{
	vector<CollisionEvent*> coEvents;
	vector<CollisionEvent*> coEventsResult;

	collision->findCollisions(dt, this, *staticObjects, coEvents);
	UINT size = coEvents.size();

	if (size == 0)
	{
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		collision->filterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) speed.vx = 0.0f;
		if (ny != 0) speed.vy = 0.0f;


		isStand = true;
	}

	for (UINT i = 0; i < size; ++i) delete coEvents[i];
}

void ITemHP::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (visible)
	{
		auto pos = &cameraGlobal->transform(x, y);
		ani->render(pos->x, pos->y, false, colorBrush);
		visible = !ani->isLastFrame();
	}
}


ITemHP::~ITemHP()
{
}

void ITemHP::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

ITemHP * ITemHP::tryCreateITemHP(float x, float y)
{
	int num = rand() % 100;// [0, 99]
	if (num > 0 && num < 39) //40.0%
	{
		num = rand() % 50;// [0, 49]
		if (num % 3) // 66.6%
			return new ITemHP(x, y, false);//small
		else
			return new ITemHP(x, y, true);//big
	}

	return null;
}
