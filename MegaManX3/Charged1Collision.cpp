#include "Charged1Collision.h"



void Charged1Collision::loadResources()
{
	spritesGlobal->addSprite(Charged1_Collision_Animation, TChargedCollision, 63, 5, 14, 14);
	//spritesGlobal->addSprite(Charged1_Collision_Animation + 1, TChargedCollision, 82, 0, 22, 23);
	auto ani = new AnimationOneTime(20);
	ani->add(Charged1_Collision_Animation);
	ani->add(Charged1_Collision_Animation + 1);
	ani->add(Charged1_Collision_Animation);
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


void Charged1Collision::setDirection(bool toLeft)
{
	directions.emplace_back(toLeft);
}

void Charged1Collision::render(DWORD dt, bool center, D3DCOLOR colorBrush)
{
	auto direction = directions.begin();
	bool isLeft = false;
	for (auto it = animations.begin(); it != animations.end(); )
	{
		isLeft = direction[0];
		auto ani = &(*it).animation;
		auto pos = cameraGlobal->transform((*it).point.x, (*it).point.y);
		if (isLeft)
			ani->renderFlipX(pos.x, pos.y, center, colorBrush);
		else
			ani->render(pos.x, pos.y, center, colorBrush);
		if (ani->isFinish())
		{
			it = animations.erase(it);
			direction = directions.erase(direction);
		}
		else ++it, ++direction;
	}
}

Charged1Collision::~Charged1Collision()
{
}
