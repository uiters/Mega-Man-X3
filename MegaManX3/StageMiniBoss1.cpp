#include "StageMiniBoss1.h"



StageMiniBoss1::StageMiniBoss1()
{
	gateLeft = new Gate(2304, 896, 16, 48, false);
	gateRight = new Gate(2546, 896, 16, 48, false);

	gateLeft->state = GateOpen;
	gateRight->state = GateLock;

	genjibo = new Genjibo(-1, 2518, 700);
	shurikein = new Shurikein(-1, 2518, 920);

	shurikein->state = manifest;
	shurikein->visible = false;
	genjibo->setShurikein(shurikein);
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
	if (gateLeft->state == GateOpen && !mainGlobal->getBoundBox().intersectsWith(gateLeft->getBoundBox()))
	{
		gateLeft->state = GateClose;
	}
	if (!shurikein->visible && mainGlobal->getBoundBox().intersectsWith(gateRight->getBoundBox()))
	{
		gateRight->state = GateOpening;
	}
	genjibo->update(dt);
	shurikein->update(dt, staticObjects);
}

void StageMiniBoss1::render(DWORD dt, D3DCOLOR colorBrush)
{
	genjibo->render(dt);
	shurikein->render(dt);
	gateLeft->render(dt);
	gateRight->render(dt);

}

void StageMiniBoss1::reset()
{
	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
	delete genjibo;
	delete shurikein;

	genjibo = new Genjibo(-1, 2518, 700);
	shurikein = new Shurikein(-1, 2518, 920);

	shurikein->state = manifest;
	shurikein->visible = false;
	genjibo->setShurikein(shurikein);
}
