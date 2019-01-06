#include "HornetPoint.h"



void HornetPoint::loadResources()
{
	_animations[Hornet_Aim] = animationsGlobal->get(Hornet_Aim);
	_animations[Hornet_Aimming] = animationsGlobal->get(Hornet_Aimming);
	state = Hornet_Aim;
}

HornetPoint::HornetPoint()
{
	loadResources();
	visible = false;
	timeHide = (2500); //2.5s
}



HornetPoint::~HornetPoint()
{
}

void HornetPoint::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 5;
	top = y + 5;
	right = x + 7;
	bottom = y + 7;
}

void HornetPoint::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	if (visible)
	{
		GameObject::update(dt);
		timeHide.update();
		if (timeHide.isStop())
		{
			visible = false;
			done = true;
		}
		else
		{
			if (isChase)
				chase();
			else
				aiming();
		}
	}
}

void HornetPoint::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (visible)
	{
		auto pos = &cameraGlobal->transform(x, y);
		_animations[state]->render(pos->x, pos->y, true);
	}
}

void HornetPoint::setLocation(float x, float y)
{
	this->x = x;
	this->y = y;
}

void HornetPoint::show()
{
	visible = true;
	timeHide.start();
	isChase = true;
	done = false;
	state = Hornet_Aim;
}

void HornetPoint::chase()
{
	float distanceX = mainGlobal->x - x;
	float distanceY = mainGlobal->y - y;

	float time = distanceX < 50.f ? 550.f : 450.f;

	speed.vy = distanceY / time; //calculate speed
	speed.vx = distanceX / time;

	collisionMain();
}

void HornetPoint::aiming()
{
	auto box = mainGlobal->getBoundBox();
	x = mainGlobal->x + box.width / 2;
	y = mainGlobal->y + box.height / 2;
}

void HornetPoint::collisionMain()
{
	if (mainGlobal->getBoundBox().intersectsWith(this->getBoundBox()) ||
		mainGlobal->collisionGameObject(mainGlobal, this))
	{
		isChase = false;
		state = Hornet_Aimming;
		timeHide.setTimeUp(7000);//7s
		timeHide.start();
	}
	else
	{
		x += dx;
		y += dy;
	}
}
