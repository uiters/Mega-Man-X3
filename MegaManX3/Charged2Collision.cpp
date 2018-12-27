#include "Charged2Collision.h"



Charged2Collision::Charged2Collision()
{
	loadResources();
}

void Charged2Collision::loadResources()
{
	spritesGlobal->addSprite(Charged2_Collision_Animation, TChargedCollision, 114, 4, 14, 20);
	spritesGlobal->addSprite(Charged2_Collision_Animation + 1, TChargedCollision, 132, 0, 24, 27);
	auto ani = new AnimationOneTime(50);
	ani->add(Charged2_Collision_Animation);
	ani->add(Charged2_Collision_Animation + 1);
	this->animation = ani;
}

Charged2Collision * Charged2Collision::_instance = nullptr;

Charged2Collision * Charged2Collision::getIntance()
{
	if (!_instance) _instance = new Charged2Collision();
	return _instance;
}

Charged2Collision::~Charged2Collision()
{
}
