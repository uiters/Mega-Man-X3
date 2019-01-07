#include "StageByte.h"



StageByte::StageByte()
{
	gateLeft = new Gate(5631, 894, 16, 48, false);
	gateRight = new Gate(5874, 489, 16, 48, false);
	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
}


StageByte::~StageByte()
{
}

void StageByte::getStaticObjects(unordered_map<int, GameObject*>* saticObjects)
{
}

void StageByte::getDynamicObjects(unordered_map<int, GameObject*>* dynamicObjects)
{
}

void StageByte::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects)
{
}

void StageByte::render(DWORD dt, D3DCOLOR colorBrush)
{
	gateLeft->render(dt);
	gateRight->render(dt);
}

void StageByte::reset()
{
	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
}
