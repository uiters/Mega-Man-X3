#include "MegamanWeapon.h"



void MegamanWeapon::update(DWORD dt)
{
	for (auto it = weapons.begin(); it  != weapons.end(); ++it )
	{
		if ((*it)->toLeft)
			(*it)->x -= 0.05f * dt;
		else (*it)->x += 0.05f * dt;
	}
}

void MegamanWeapon::render(DWORD dt, D3DCOLOR colorBrush)
{
	for (auto it = weapons.begin(); it != weapons.end(); ++it)
	{
		(*it)->render(dt, colorBrush);
	}
}

void MegamanWeapon::createWeapon(float x, float y, int level, bool isLeft)
{
	switch (level)
	{
	case 0:
		weapons.emplace_back(new BusterShot(x, y, isLeft));
		break;
	case 1:
		weapons.emplace_back(new ChargedShot1(x, y, isLeft));
		break;
	default:
		weapons.emplace_back(new ChargedShot2(x, y, isLeft));
		break;
	}
}

MegamanWeapon::MegamanWeapon()
{

}


MegamanWeapon::~MegamanWeapon()
{
}
