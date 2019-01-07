#include "Gate.h"
#include "Camera.h"


void Gate::loadResources()
{
	_animations[GateOpen] = animationsGlobal->get(GateOpen);
	if (gateBoss)
		_animations[GateLock] = animationsGlobal->get(Gate1Lock),
		_animations[GateOpening] = animationsGlobal->get(Gate1Open),
		_animations[GateClose] = animationsGlobal->get(Gate1Close);
	else
		_animations[GateLock] = animationsGlobal->get(Gate2Lock),
		_animations[GateOpening] = animationsGlobal->get(Gate2Open),
		_animations[GateClose] = animationsGlobal->get(Gate2Close);
}

Gate::Gate(int x, int y, int width, int height, bool gateBoss) : StaticObject(0, x, y, width, height)
{
	this->gateBoss = gateBoss;
	loadResources();
	state = GateLock;
}

void Gate::render(DWORD dt, D3DCOLOR colorBrush) {
	if (state == GateClose && _animations[state]->isLastFrame())
	{
		_animations[state]->reset();
		state = GateLock;
	}
	if (state == GateOpening && _animations[state]->isLastFrame())
	{
		_animations[state]->reset();
		state = GateOpen;
	}
	auto pos = &cameraGlobal->transform(x, y);
	_animations[state]->render(pos->x, pos->y);
}

Gate::~Gate()
{
}
