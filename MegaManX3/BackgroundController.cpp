#include "BackgroundController.h"



void BackgroundController::loadResources()
{
#pragma region Background
	texturesGlobal->add(TBackground, BACK_GROUND);
	spritesGlobal->addSprite(BackgroundAni, TBackground, 0, 0, 512, 256);
	spritesGlobal->addSprite(BackgroundAni + 1, TBackground, 0, 258, 512, 256);
	spritesGlobal->addSprite(BackgroundAni + 2, TBackground, 0, 516, 512, 256);
	spritesGlobal->addSprite(BackgroundAni + 3, TBackground, 0, 774, 512, 256);
	spritesGlobal->addSprite(BackgroundAni + 4, TBackground, 0, 1032, 512, 256);
	spritesGlobal->addSprite(BackgroundAni + 5, TBackground, 0, 1290, 512, 256);
	spritesGlobal->addSprite(BackgroundAni + 6, TBackground, 0, 1548, 512, 256);

	auto ani = new CAnimation(100);
	for (int i = 0; i < 7; ++i)
	{
		ani->add(BackgroundAni + i);
	}
	animationsGlobal->add(BackgroundAni, ani);

#pragma endregion

#pragma region Background 2
	texturesGlobal->add(TBackground2, BACK_GROUND_2);
	spritesGlobal->addSprite(Background2Ani, TBackground2, 0, 0, 512, 427);
#pragma endregion

	
}

BackgroundController::BackgroundController()
{
	loadResources();
	backgrounds[4] = new Background(BackgroundAni, true, 1536, 0, 512, 256, true, true);//run mini boss 1
	backgrounds[5] = new Background(BackgroundAni, true, 2178, 720, 512, 256, false, false);//mini boss 1
	backgrounds[6] = new Background(Background2Ani, false, 2817, 511, 512, 427, true, false); //mini boss 2
	backgrounds[8] = new Background(BackgroundAni, true, 5761, 951, 512, 256, true, true); // run wait boss
	backgrounds[10] = new Background(BackgroundAni, true, 7555, 1457, 512, 256, true, true);//boss
}



BackgroundController::~BackgroundController()
{
}

void BackgroundController::render(DWORD dt)
{
	if (currentBackground)
	{
		currentBackground->render(dt);
	}
	if (cameraGlobal->isSwitchState() && preBackground) //don't update
	{
		preBackground->render(dt);
	}
}

void BackgroundController::update(DWORD dt)
{
	auto index = cameraGlobal->getState();
	currentBackground = backgrounds[index];
	preBackground = backgrounds[index - 1];
	if (currentBackground)
		currentBackground->update(viewPortGlobal);
	
}
