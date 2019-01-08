#include "Stage8.h"



Stage8::Stage8()
{
	gateLeft = new Gate(5888, 896, 16, 48, false);
	gateRight = new Gate(7408, 1664, 16, 48, true);

	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
	ready = false;
	gateLeftClose = false;

	ready = true;//test 
	gateLeft->state = GateLock;//test
}


Stage8::~Stage8()
{
}

void Stage8::getStaticObjects(unordered_map<int, GameObject*>* saticObjects)
{
}

void Stage8::getDynamicObjects(unordered_map<int, GameObject*>* dynamicObjects)
{
}

void Stage8::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects)
{
	if (gateLeft->getBoundBox().intersectsWith(*viewPortGlobal))
	{
		drawLeft = true;
	}
	else drawLeft = false;

	if (ready)
	{
		if (gateRight->getBoundBox().intersectsWith(*viewPortGlobal))
		{
			drawRight = true;
			if (mainGlobal->getBoundBox().intersectsWith(gateRight->getBoundBox()))
			{
				gateRight->state = GateOpening;
				main->enable = false;
				main->speed.vx = 0.005f * dt;
				ready = false;
			}
		}
		else drawRight = false;
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

void Stage8::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (drawLeft)
		gateLeft->render(dt);
	else
		if (drawRight)
			gateRight->render(dt);
}

void Stage8::reset()
{
	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
	ready = false;
	gateLeftClose = false;
}
