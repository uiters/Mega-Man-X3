#include "StageMiniBoss2.h"



StageMiniBoss2::StageMiniBoss2()
{
	boss = new SolskjærController();
	main = dynamic_cast<MegamanX*>(mainGlobal);
	gateRight = new Gate(5616, 896, 16, 48, false);
	gateLeft = new Gate(2560, 896, 16, 48, false);
	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
	ready = false;
	gateLeftClose = false;

	drawLeft = true;
	drawRight = false;

	ready = true;//test

}


StageMiniBoss2::~StageMiniBoss2()
{
}

void StageMiniBoss2::getStaticObjects(unordered_map<int, GameObject*>* saticObjects)
{
}

void StageMiniBoss2::getDynamicObjects(unordered_map<int, GameObject*>* dynamicObjects)
{
}

void StageMiniBoss2::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects)
{
	if (ready)
	{
		if (!main->enable && gateLeft->state == GateLock)
			main->setEnable(true);
		if (!miniBoss)
		{
			if (!doneMiniBoss && viewPortGlobal->x >= 4736.f && viewPortGlobal->x < 4960.f)
				miniBoss = true,
				doneMiniBoss = true,
				cameraGlobal->setEnable(false);
		}
		else // in miniboss
		{
			if (viewPortGlobal->x + 5 < 4856.f)
				viewPortGlobal->x += 5;
			else viewPortGlobal->x = 4856.f;
			boss->update(dt, staticObjects, main);
			if (boss->getIsFinish())
			{
				cameraGlobal->setEnable(true);
				miniBoss = false;
			}
		}

		if (gateLeft->getBoundBox().intersectsWith(*viewPortGlobal))
		{
			drawLeft = true;
		}
		else
		{
			drawLeft = true;
			if (gateRight->getBoundBox().intersectsWith(*viewPortGlobal))
				drawRight = true;
			else drawRight = false;
		}
	}
	else
	{
		if (gateRight->state == GateLock)
		{
			if (gateLeftClose && gateLeft->state == GateLock)
				ready = true;
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

void StageMiniBoss2::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (miniBoss)
		boss->render(dt);

	if (drawLeft)
		gateLeft->render(dt);
	else 
	if (drawRight)
		gateRight->render(dt);
}

void StageMiniBoss2::reset()
{
	miniBoss = false;
	doneMiniBoss = false;
	cameraGlobal->setEnable(true);
	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
	delete boss;
	boss = new SolskjærController();
	ready = false;
	gateLeftClose = false;
	drawLeft = true;
	drawRight = false;
}
