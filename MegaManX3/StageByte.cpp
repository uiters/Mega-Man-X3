#include "StageByte.h"



StageByte::StageByte()
{
	gateLeft = new Gate(5631, 896, 16, 48, false);
	gateRight = new Gate(5874, 896, 16, 48, false);
	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
	ready = false;
	gateLeftClose = false;
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

void StageByte::render(DWORD dt, D3DCOLOR colorBrush)
{
	gateLeft->render(dt);
	gateRight->render(dt);
}

void StageByte::reset()
{
	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
	ready = false;
	gateLeftClose = false;
}
