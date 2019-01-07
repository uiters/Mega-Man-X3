#include "Stage8.h"



Stage8::Stage8()
{
	gateLeft = new Gate(5904, 849, 16, 48, false);
	gateRight = new Gate(7408, 1664, 16, 48, true);

	gateLeft->state = GateOpen;
	gateRight->state = GateLock;
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
		drawLeft = true;
	else
	{
		drawLeft = true;
		if (gateRight->getBoundBox().intersectsWith(*viewPortGlobal))
			drawRight = true;
		else drawRight = false;
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
}
