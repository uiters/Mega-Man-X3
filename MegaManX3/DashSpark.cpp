#include "DashSpark.h"

void DashSpark::loadResources()
{
	auto ani = new AnimationOneTime(40);
	for (int i = 0; i < 10; ++i)
	{
		spritesGlobal->add(DashSparkAnimation + i, TDashSpark, i * 35, 0, (i + 1) * 35, 32);
		ani->add(DashSparkAnimation + i);
	}
	animationsGlobal->add(TDashSpark, ani);
	this->animation = ani;
}

DashSpark::DashSpark()
{
	loadResources();
}

DashSpark::~DashSpark()
{
}

void DashSpark::setDirection(bool isLeft)
{
	this->isLeft = isLeft;
}

void DashSpark::render(DWORD dt, bool center, D3DCOLOR colorBrush)
{
	for (auto it = animations.begin(); it != animations.end(); )
	{
		auto ani = &(*it).animation;
		auto pos = cameraGlobal->transform((*it).point.x, (*it).point.y);
		if(isLeft) 
			ani->render(pos.x, pos.y, center, colorBrush);
		else ani->renderFlipX(pos.x, pos.y, center, colorBrush);

		if (ani->isFinish())
		{
			it = animations.erase(it);
		}
		else ++it;
	}
}

DashSpark * DashSpark::_instance = null;

DashSpark * DashSpark::getInstance()
{
	if (!_instance) _instance = new DashSpark();
	return _instance;
}
