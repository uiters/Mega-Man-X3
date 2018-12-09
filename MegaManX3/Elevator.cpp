#include "Elevator.h"



Elevator::Elevator()
{
}


Elevator::Elevator(UINT idTexture, float x, float y) : DynamicObject(idTexture, x, y, 0, 0)
{

}

Elevator::~Elevator()
{
}

void Elevator::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

void Elevator::update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects)
{
}

void Elevator::render(DWORD dt, D3DCOLOR colorBrush)
{
}
