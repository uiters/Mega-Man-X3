#include "DashSmoke.h"

DashSmoke* DashSmoke::_instance = null;
void DashSmoke::loadResources()
{
	auto ani = new AnimationOneTime(40);
	for (int i = 0; i < 12; ++i)
	{
		spritesGlobal->add(DashSmokeAnimation + i, TDashSmoke, i * 13.75, 0, (i + 1) * 13.75, 27);
		ani->add(DashSmokeAnimation + i);
	}
	animationsGlobal->add(TDashSmoke, ani);
	this->animation = ani;
}

DashSmoke::DashSmoke()
{
	loadResources();
}


DashSmoke::~DashSmoke()
{

}

DashSmoke * DashSmoke::getInstance()
{
	if (!_instance) _instance = new DashSmoke();
	return _instance;
}
