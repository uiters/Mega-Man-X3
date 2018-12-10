#include "Elevator.h"

Elevator::Elevator(UINT idTexture, float x, float y) : StaticObject(idTexture, x, y - 6, 96, 43)
{
	//y -= 28;
}

Elevator::~Elevator()
{

}

void Elevator::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y + 8;
	right = x + 96;
	bottom = y + 43;
}

void Elevator::update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects , unordered_map<int, CTreeObject*>* dynamicObjects) 
{
	GameObject::update(dt);
	if (isRun)
	{
		y += dy;
		if (y <= 438)
		{
			isRun = false;
			speed.vy = 0;
			//mainGlobal->speed.vy = speed.vy;
			return;
		}
	}
}

void Elevator::render(DWORD dt, D3DCOLOR colorBrush)
{
	auto pos = cameraGlobal->transform(x, y);
	_animations[TElevator]->render(pos.x, pos.y);
}

void Elevator::run()
{
	speed.vy = -0.015f;
	isRun = true;
}

