#include "ChargedEffect.h"

void ChargedEffect::loadResources()
{
	auto ani1 = new CAnimation(20);
	auto ani2 = new CAnimation(20);

	for (int i = 0; i < 11; ++i)
	{
		spritesGlobal->add(Charged_Level1 + i, TCharged1, i * 47 + 1, 0, (i + 1) * 47, 46);
		spritesGlobal->add(Charged_Level2 + i, TCharged2, i * 48 + 1, 0, (i + 1) * 48, 50);
		ani1->add(Charged_Level1 + i, 10);
		ani2->add(Charged_Level2 + i, 10);
	}
	animationsGlobal->add(TCharged1, ani1);
	animationsGlobal->add(TCharged2, ani2);
}
ChargedEffect* ChargedEffect::_instance = null;
ChargedEffect * ChargedEffect::getInstance()
{
	if (!_instance) _instance = new ChargedEffect();
	return _instance;
}

void ChargedEffect::createCharged(int level)
{
	ani = animationsGlobal->get(anis[level - 1]);
}

void ChargedEffect::render(int x, int y, bool center, D3DCOLOR colorBrush)
{
	auto pos = cameraGlobal->transform(x, y);
	ani->render(pos.x, pos.y, center, colorBrush);
}

void ChargedEffect::stop()
{
	ani = null;
}

ChargedEffect::ChargedEffect()
{
	loadResources();
}

void ChargedEffect::createEffect(float x, float y)
{
}


ChargedEffect::~ChargedEffect()
{
}
