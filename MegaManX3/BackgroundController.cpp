#include "BackgroundController.h"



void BackgroundController::loadResources()
{
	texturesGlobal->add(TBackgroundBoss, BACKGROUNDBOSS);

	spritesGlobal->addSprite(BackgroundBoss, TBackgroundBoss, 0, 0, 512, 256);
	spritesGlobal->addSprite(BackgroundBoss + 1, TBackgroundBoss, 0, 258, 256, 256);
	spritesGlobal->addSprite(BackgroundBoss + 2, TBackgroundBoss, 0, 516, 256, 256);
	spritesGlobal->addSprite(BackgroundBoss + 3, TBackgroundBoss, 0, 774, 256, 256);
	spritesGlobal->addSprite(BackgroundBoss + 4, TBackgroundBoss, 0, 1032, 256, 256);
	spritesGlobal->addSprite(BackgroundBoss + 5, TBackgroundBoss, 0, 1290, 256, 256);
	spritesGlobal->addSprite(BackgroundBoss + 6, TBackgroundBoss, 0, 1548, 256, 256);

	auto ani = new CAnimation(100);
	for (int i = 0; i < 7; ++i)
	{
		ani->add(BackgroundBoss + i);
	}
	backgroundBoss = ani;
}

BackgroundController::BackgroundController()
{
	loadResources();
}



BackgroundController::~BackgroundController()
{
}

void BackgroundController::render(DWORD dt)
{
	backgroundBoss->render(0, -96);
}

void BackgroundController::update(DWORD dt)
{
}
