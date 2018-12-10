#include "MegamanEffectFactory.h"

MegamanEffectFactory::MegamanEffectFactory()
{
	dashSmoke = DashSmoke::getInstance();
	dashSpark = DashSpark::getInstance();
	wallKick = WallKick::getInstance();
	wallSlide = WallSlide::getInstance();
}


MegamanEffectFactory::~MegamanEffectFactory()
{

}

void MegamanEffectFactory::createDashSmoke(float x, float y)
{
	dashSmoke->createEffect(x, y);
}

void MegamanEffectFactory::createDashSpark(float x, float y)
{
	dashSpark->createEffect(x, y);
}

void MegamanEffectFactory::createWallKick(float x, float y)
{
	wallKick->createEffect(x, y);
}

void MegamanEffectFactory::createWallSlide(float x, float y)
{
	wallSlide->createEffect(x, y);
}

void MegamanEffectFactory::stopDashSpark()
{
	dashSpark->stop();
}

void MegamanEffectFactory::render(DWORD dt, D3DCOLOR colorBrush)
{
	wallSlide->render(dt, true, colorBrush);
	dashSpark->render(dt, true, colorBrush);
	dashSmoke->render(dt, true, colorBrush);
	wallKick->render(dt, true, colorBrush);
	
}
