#include "MegamanEffectFactory.h"

MegamanEffectFactory::MegamanEffectFactory()
{
	dashSmoke = DashSmoke::getInstance();
	dashSpark = DashSpark::getInstance();
	wallKick = WallKick::getInstance();
	wallSlide = WallSlide::getInstance();
	charged = ChargedEffect::getInstance();
}


MegamanEffectFactory::~MegamanEffectFactory()
{

}

void MegamanEffectFactory::createDashSmoke(float x, float y)
{
	dashSmoke->createEffect(x, y);
}

void MegamanEffectFactory::createDashSpark(float x, float y, bool isLeft)
{
	dashSpark->createEffect(x, y);
	dashSpark->setDirection(isLeft);
}

void MegamanEffectFactory::createWallKick(float x, float y)
{
	wallKick->createEffect(x, y);
}

void MegamanEffectFactory::createWallSlide(float x, float y)
{
	wallSlide->createEffect(x, y);
}

void MegamanEffectFactory::createShoot(int level)
{
	charged->createCharged(level);
	isCharge = true;
}

void MegamanEffectFactory::stopDashSpark()
{
	dashSpark->stop();
}

void MegamanEffectFactory::stopShoot()
{
	isCharge = false;
}

void MegamanEffectFactory::render(DWORD dt, float x, float y, int width, int height, D3DCOLOR colorBrush)
{
	wallSlide->render(dt, true, colorBrush);
	dashSpark->render(dt, true, colorBrush);
	dashSmoke->render(dt, true, colorBrush);
	wallKick->render(dt, true, colorBrush);
	if (isCharge)
		charged->render(x + width / 2, y + height / 2, true, colorBrush);
}
