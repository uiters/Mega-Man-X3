#include "StageWaitBoss.h"



StageWaitBoss::StageWaitBoss()
{
	gateLeft = new Gate(7424, 1664, 16, 48, true);
	gateRight = new Gate(7664, 1664, 16, 48, true);

	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
}


StageWaitBoss::~StageWaitBoss()
{
}

void StageWaitBoss::getStaticObjects(unordered_map<int, GameObject*>* saticObjects)
{
}

void StageWaitBoss::getDynamicObjects(unordered_map<int, GameObject*>* dynamicObjects)
{
}

void StageWaitBoss::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects)
{
}

void StageWaitBoss::render(DWORD dt, D3DCOLOR colorBrush)
{
	gateLeft->render(dt);
	gateRight->render(dt);
}

void StageWaitBoss::reset()
{
	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
}
