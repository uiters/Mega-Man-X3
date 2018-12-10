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

DashSpark * DashSpark::_instance = null;

DashSpark * DashSpark::getInstance()
{
	if (!_instance) _instance = new DashSpark();
	return _instance;
}
