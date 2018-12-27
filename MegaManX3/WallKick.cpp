#include "WallKick.h"



void WallKick::loadResources()
{
	auto ani = new AnimationOneTime(50);
	spritesGlobal->addSprite(KickAnimation, TKick, 0, 0, 11, 12);
	ani->add(KickAnimation);
	//animationsGlobal->add(TKick, ani);
	this->animation = ani;
}

WallKick::WallKick()
{
	loadResources();
}

WallKick::~WallKick()
{
}

WallKick* WallKick::_instance = null;

WallKick * WallKick::getInstance()
{
	if (!_instance) _instance = new WallKick();
	return _instance;
}
