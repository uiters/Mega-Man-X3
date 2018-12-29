#include "Charged2Collision.h"



Charged2Collision::Charged2Collision()
{
	loadResources();
}

void Charged2Collision::loadResources()
{
	spritesGlobal->addSprite(Charged2_Collision_Animation, TChargedCollision, 114, 4, 14, 20);
	//spritesGlobal->addSprite(Charged2_Collision_Animation + 1, TChargedCollision, 132, 0, 24, 27);
	auto ani = new AnimationOneTime(20);
	ani->add(Charged2_Collision_Animation);
	ani->add(Charged2_Collision_Animation + 1);
	ani->add(Charged2_Collision_Animation);
	this->animation = ani;
}

Charged2Collision * Charged2Collision::_instance = nullptr;

Charged2Collision * Charged2Collision::getIntance()
{
	if (!_instance) _instance = new Charged2Collision();
	return _instance;
}

void Charged2Collision::setDirection(bool toLeft)
{
	directions.emplace_back(toLeft);
}

void Charged2Collision::render(DWORD dt, bool center, D3DCOLOR colorBrush)
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

Charged2Collision::~Charged2Collision()
{
}
