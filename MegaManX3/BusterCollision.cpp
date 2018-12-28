#include "BusterCollision.h"



BusterCollision::BusterCollision()
{
	loadResources();
}

void BusterCollision::loadResources()
{
	spritesGlobal->addSprite(Buster_Collision_Animation, TChargedCollision, 5, 7, 12, 12);
	spritesGlobal->addSprite(Buster_Collision_Animation + 1, TChargedCollision, 22, 6, 13, 13);
	spritesGlobal->addSprite(Buster_Collision_Animation + 2, TChargedCollision, 40, 5, 15, 15);
	auto ani = new AnimationOneTime(30);
	ani->add(Buster_Collision_Animation, 30);
	ani->add(Buster_Collision_Animation + 1, 20);
	ani->add(Buster_Collision_Animation + 2, 20);
	this->animation = ani;
}

BusterCollision * BusterCollision::_instance = nullptr;

BusterCollision * BusterCollision::getIntance()
{
	if (!_instance) _instance = new BusterCollision();
	return _instance;
}

BusterCollision::~BusterCollision()
{
}
