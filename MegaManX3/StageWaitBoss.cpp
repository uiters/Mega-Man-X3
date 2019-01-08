#include "StageWaitBoss.h"



StageWaitBoss::StageWaitBoss()
{
	gateLeft = new Gate(7424, 1664, 16, 48, true);
	gateRight = new Gate(7664, 1664, 16, 48, true);

	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
	ready = false;
	gateLeftClose = false;
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
	if (ready)
	{
		if (mainGlobal->getBoundBox().intersectsWith(gateRight->getBoundBox()))
		{
			gateRight->state = GateOpening;
			main->enable = false;
			main->speed.vx = 0.005f * dt;
			ready = false;
		}
	}
	else
	{
		if (gateRight->state == GateLock)
		{
			if (gateLeftClose && gateLeft->state == GateLock)
				ready = true,
				main->setEnable(true);
			updateMain(dt);
		}

		else
			if (!main->enable && gateRight->state == GateOpen)
			{
				updateMain(dt);
			}

		if (gateLeft->state == GateOpen && !mainGlobal->getBoundBox().intersectsWith(gateLeft->getBoundBox()))
		{
			gateLeft->state = GateClose;
			gateLeftClose = true;
			updateMain(dt);
			main->speed.vx = 0.0f;
			main->dx = 0;
			main->state = stand;
		}
	}
}

void StageWaitBoss::render(DWORD dt, D3DCOLOR colorBrush)
{
	gateLeft->render(dt);
	gateRight->render(dt);
}

void StageWaitBoss::reset()
{
	gateRight->state = GateLock;
	gateLeftClose = false;
	if (pointRevival)
		ready = true,
		gateLeft->state = GateLock;
	else
		ready = false,
		gateLeft->state = GateOpen;
}
