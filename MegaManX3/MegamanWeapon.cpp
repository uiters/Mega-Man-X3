#include "MegamanWeapon.h"



void MegamanWeapon::update(DWORD dt)
{
	for (auto it = weapons->begin(); it  != weapons->end(); ++it )
	{
		it[0]->update(dt);
	}
}

void MegamanWeapon::render(DWORD dt, D3DCOLOR colorBrush)
{
	for (auto it = weapons->begin(); it != weapons->end(); )
	{
		(*it)->render(dt, colorBrush);

		if (!it[0]->getBoundBox().intersectsWith(cameraGlobal->viewport))
		{
			delete (*it);
			it = weapons->erase(it);
		}
		else ++it;
	}
}

void MegamanWeapon::createWeapon(float x, float y, int level, bool isLeft)
{
	switch (level)
	{
	case 0:
		weapons->emplace_back(new BusterShot(x, y, isLeft));
		break;
	case 1:
		weapons->emplace_back(new ChargedShot1(x, y, isLeft));
		break;
	default:
		weapons->emplace_back(new ChargedShot2(x, y, isLeft));
		break;
	}
}

MegamanWeapon::MegamanWeapon(vector<Weapon*>* weapons)
{
	this->weapons = weapons;
}




MegamanWeapon::~MegamanWeapon()
{
}
