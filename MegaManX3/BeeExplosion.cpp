#include "BeeExplosion.h"
#include "ConstGlobals.h"


void BeeExplosion::loadResources()
{
	//bee explosion
	spritesGlobal->addSprite(Hornet_Bee_Explosion, TBlastHornet, 186, 186, 16, 16);
	spritesGlobal->addSprite(Hornet_Bee_Explosion + 1, TBlastHornet, 205, 183, 20, 20);
	spritesGlobal->addSprite(Hornet_Bee_Explosion + 2, TBlastHornet, 228, 181, 24, 24);
	spritesGlobal->addSprite(Hornet_Bee_Explosion + 2, TBlastHornet, 254, 180, 26, 26);
	spritesGlobal->addSprite(Hornet_Bee_Explosion + 3, TBlastHornet, 283, 178, 32, 30);
	spritesGlobal->addSprite(Hornet_Bee_Explosion + 4, TBlastHornet, 319, 177, 32, 32);
	spritesGlobal->addSprite(Hornet_Bee_Explosion + 5, TBlastHornet, 354, 176, 34, 34);

	//bee explosion
	auto ani = new AnimationOneTime(50);
	int time1 = 130;
	for (int i = 0; i < 6; ++i)
	{
		ani->add(Hornet_Bee_Explosion + i, time1 - i * 15);
	}
	animation = ani;
}

BeeExplosion::BeeExplosion()
{
	loadResources();
}


BeeExplosion::~BeeExplosion()
{
}

BeeExplosion * BeeExplosion::_instance = null;

BeeExplosion * BeeExplosion::getInstance()
{
	if (!_instance) _instance = new BeeExplosion();
	return _instance;
}
