#include "WeaponEffectController.h"



WeaponEffectController::WeaponEffectController()
{
	smoke = WallSlide::getInstance();
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

void WeaponEffectController::render(DWORD dt)
{
	smoke->render(dt, true);
}

