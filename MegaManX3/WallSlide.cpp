#include "WallSlide.h"

void WallSlide::loadResources()
{
	auto ani = new AnimationOneTime(50);
	spritesGlobal->addSprite(SlideAnimation, TSlide, 0, 0, 8, 15);
	spritesGlobal->addSprite(SlideAnimation + 1, TSlide, 12, 0, 10, 15);
	spritesGlobal->addSprite(SlideAnimation + 2, TSlide, 29, 0, 13, 15);
	spritesGlobal->addSprite(SlideAnimation + 3, TSlide, 49, 0, 14, 15);
	spritesGlobal->addSprite(SlideAnimation + 4, TSlide, 70, 0, 14, 15);
	spritesGlobal->addSprite(SlideAnimation + 5, TSlide, 89, 0, 14, 15);

	for (int i = 0; i < 6; ++i)
	{
		ani->add(SlideAnimation + i);
	}
	//animationsGlobal->add(TSlide, ani);
	this->animation = ani;
}

WallSlide::WallSlide()
{
	loadResources();
}

WallSlide::~WallSlide()
{
}

WallSlide * WallSlide::_instance = null;

WallSlide * WallSlide::getInstance()
{
	if (!_instance) _instance = new WallSlide();
	return _instance;
}
