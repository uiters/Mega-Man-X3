#include "HornetExplosion.h"



void HornetExplosion::loadResources()
{
	//explosion
	spritesGlobal->addSprite(Hornet_Explosion, TBlastHornet, 102, 231, 16, 16);
	spritesGlobal->addSprite(Hornet_Explosion + 1, TBlastHornet, 123, 223, 32, 32);
	spritesGlobal->addSprite(Hornet_Explosion + 2, TBlastHornet, 159, 226, 28, 24);
	spritesGlobal->addSprite(Hornet_Explosion + 3, TBlastHornet, 192, 224, 30, 27);
	spritesGlobal->addSprite(Hornet_Explosion + 4, TBlastHornet, 230, 223, 32, 27);
	spritesGlobal->addSprite(Hornet_Explosion + 5, TBlastHornet, 269, 220, 32, 30);
	spritesGlobal->addSprite(Hornet_Explosion + 6, TBlastHornet, 312, 220, 32, 30);
	spritesGlobal->addSprite(Hornet_Explosion + 7, TBlastHornet, 352, 220, 32, 30);

	//hornet explosion
	auto ani = new AnimationOneTime(50);
	int time = 120;
	for (int i = 0; i < 8; ++i)
	{
		ani->add(Hornet_Explosion + i, time - i * 12);
	}
	animationsGlobal->add(Hornet_Explosion, ani);

	animation= ani;

}

HornetExplosion::HornetExplosion()
{
	loadResources();
}


HornetExplosion::~HornetExplosion()
{

}

HornetExplosion * HornetExplosion::_instance = null;

HornetExplosion * HornetExplosion::getInstance()
{
	if (!_instance) _instance = new HornetExplosion();
	return _instance;
}
