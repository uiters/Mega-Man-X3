#include "StageMiniBoss2.h"



StageMiniBoss2::StageMiniBoss2()
{
	boss = new SolskjærController();
	main = dynamic_cast<MegamanX*>(mainGlobal);
	gateRight = new Gate(5616, 896, 16, 48, false);
	gateLeft = new Gate(2560, 896, 16, 48, false);
	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
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
	if (!miniBoss)
	{
		if (!doneMiniBoss && viewPortGlobal->x >= 4864.f)
			miniBoss = true,
			doneMiniBoss = true,
			viewPortGlobal->x = 4864,
			cameraGlobal->setEnable(false);
	}
	else // in miniboss
	{
		boss->update(dt, staticObjects, main);
		if (true)
		{
			cameraGlobal->setEnable(true);
			miniBoss = false;
		}
	}

	if (gateLeft->getBoundBox().intersectsWith(*viewPortGlobal))
	{
		drawLeft = true;
		if(gateLeft->state == GateOpen && !mainGlobal->getBoundBox().intersectsWith(gateLeft->getBoundBox()))
		{
			gateLeft->state = GateClose;
		}
	}
	else
	{
		drawLeft = true;
		if (gateRight->getBoundBox().intersectsWith(*viewPortGlobal))
			drawRight = true;
		else drawRight = false;
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
}
