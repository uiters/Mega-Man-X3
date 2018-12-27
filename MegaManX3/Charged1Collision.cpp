#include "Charged1Collision.h"



void Charged1Collision::loadResources()
{
	spritesGlobal->addSprite(Charged1_Collision_Animation, TChargedCollision, 63, 5, 14, 14);
	spritesGlobal->addSprite(Charged1_Collision_Animation + 1, TChargedCollision, 82, 0, 22, 23);
	auto ani = new AnimationOneTime(50);
	ani->add(Charged1_Collision_Animation);
	ani->add(Charged1_Collision_Animation + 1);
	this->animation = ani;
}

Charged1Collision::Charged1Collision()
{
	loadResources();
}

Charged1Collision * Charged1Collision::_instance = nullptr;

Charged1Collision * Charged1Collision::getIntance()
{
	if (!_instance) _instance = new Charged1Collision();
	return _instance;
}


Charged1Collision::~Charged1Collision()
{
}
