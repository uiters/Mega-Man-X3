#include "WeaponEffectController.h"



WeaponEffectController::WeaponEffectController()
{
	smoke = WallSlide::getInstance();
	charged1 = Charged1Collision::getIntance();
	charged2 = Charged2Collision::getIntance();
	buster = BusterCollision::getIntance();
}

WeaponEffectController * WeaponEffectController::_instance = nullptr;

WeaponEffectController * WeaponEffectController::getIntance()
{
	if (!_instance) _instance = new WeaponEffectController();
	return _instance;
}

WeaponEffectController::~WeaponEffectController()
{
}

void WeaponEffectController::createBulletSmoke(float x, float y)
{
	smoke->createEffect(x, y);
}

void WeaponEffectController::createBusterEffect(float x, float y, bool toLeft)
{
	buster->createEffect(x, y);
}

void WeaponEffectController::createCharged1Effect(float x, float y, bool toLeft)
{
	charged1->createEffect(x, y);
	charged1->setDirection(toLeft);
}

void WeaponEffectController::createCharged2Effect(float x, float y, bool toLeft)
{
	charged2->createEffect(x, y);
	charged2->setDirection(toLeft);
}

void WeaponEffectController::render(DWORD dt)
{
	smoke->render(dt, true);
	buster->render(dt, true);
	charged1->render(dt, true);
	charged2->render(dt, true);
}

