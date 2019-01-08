#include "StageMiniBoss1.h"



StageMiniBoss1::StageMiniBoss1()
{
	gateLeft = new Gate(2304, 897, 16, 48, false);
	gateRight = new Gate(2546, 897, 16, 48, false);

	gateLeft->state = GateOpen;
	gateRight->state = GateLock;

	genjibo = new Genjibo(-1, 2518, 700);
	shurikein = new Shurikein(-1, 2518, 920);

	shurikein->state = manifest;
	shurikein->visible = false;
	genjibo->setShurikein(shurikein);

	ready = false;
	gateLeftClose = false;
}


StageMiniBoss1::~StageMiniBoss1()
{
}

void StageMiniBoss1::getStaticObjects(unordered_map<int, GameObject*>* saticObjects)
{
	if(shurikein->visible)
		saticObjects[0][-777] = gateRight;
}

void StageMiniBoss1::getDynamicObjects(unordered_map<int, GameObject*>* dynamicObjects)
{
	dynamicObjects[0][-888] = genjibo;
	dynamicObjects[0][-889] = shurikein;
}

void StageMiniBoss1::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects)
{
	if (ready)
	{
		genjibo->update(dt);
		shurikein->update(dt, staticObjects);
		if (!main->enable && shurikein->state != manifest)
			main->setEnable(true);

		if (!shurikein->visible && main->enable &&
			mainGlobal->getBoundBox().intersectsWith(gateRight->getBoundBox()))
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
			if(gateLeftClose && gateLeft->state == GateLock)
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

void StageMiniBoss1::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (ready)
	{
		genjibo->render(dt);
		shurikein->render(dt);
	}

	gateLeft->render(dt);
	gateRight->render(dt);

}

void StageMiniBoss1::reset()
{
	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
	delete genjibo;
	delete shurikein;
	ready = false;
	gateLeftClose = false;


	genjibo = new Genjibo(-1, 2518, 700);
	shurikein = new Shurikein(-1, 2518, 920);

	shurikein->state = manifest;
	shurikein->visible = false;
	genjibo->setShurikein(shurikein);
}
