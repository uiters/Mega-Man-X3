#include "StageBoss.h"



StageBoss::StageBoss()
{
	gateLeft = new Gate(7680, 1664, 16, 48, true);
	gateLeft->state = GateOpen;
	boss = new BlastHornet();
	hpBarBoss = new HPBar(*boss->getHp(), 32.0f, 1.0f, false);
	ready = false;
	gateLeftClose = false;
}


StageBoss::~StageBoss()
{
}

void StageBoss::getStaticObjects(unordered_map<int, GameObject*>* saticObjects)
{
}

void StageBoss::getDynamicObjects(unordered_map<int, GameObject*>* dynamicObjects)
{
	dynamicObjects[0][-9988] = boss;
}

void StageBoss::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects)
{
	
	if (ready)
	{
		if (!main->enable && boss->state != Hornet_Show)
			main->setEnable(true);
		boss->update(dt, staticObjects);
	}
	else
	{
		if (gateLeftClose && gateLeft->state == GateLock)
			ready = true,
			updateMain(dt);
		else
			if (!main->enable )
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

void StageBoss::render(DWORD dt, D3DCOLOR colorBrush)
{
	gateLeft->render(dt);
	boss->render(dt);
}

void StageBoss::reset()
{
	boss->reset();
	gateLeft->state = GateOpen;
	ready = false;
	gateLeftClose = false;
}
