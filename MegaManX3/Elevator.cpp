#include "Elevator.h"

void Elevator::loadResources()
{
	_animations[TElevator] = animationsGlobal->get(TElevator);
}

Elevator::Elevator(UINT id, float x, float y) : StaticObject(id, x + 2, 684, 96, 43)
{
	//y -= 28;
	loadResources();
}

Elevator::~Elevator()
{

}

void Elevator::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 12;
	top = y + 10;
	right = x + 70;
	bottom = y + 43;
}

void Elevator::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects , unordered_map<int, GameObject*>* dynamicObjects) 
{
	this->dt = dt;
	//GameObject::update(dt);
	this->dy = speed.vy * dt;
	if (isRun && y >= 170)
	{
		y += this->dy;
	}
	else
		isRun = false,
		speed.vy = 0.0f,
		this->dy = 0.0f;
}

void Elevator::render(DWORD dt, D3DCOLOR colorBrush)
{
	auto pos = cameraGlobal->transform(x, y);
	_animations[TElevator]->render(pos.x, pos.y);
	//y += 1;
}

void Elevator::run()
{
	if (y < 170) return;
	this->speed.vy = -0.028f;
	isRun = true;
}

