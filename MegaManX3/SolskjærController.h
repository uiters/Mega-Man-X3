#pragma once
#include<vector>

#include "BarrierSystem.h"
#include "Solskjær.h"
#include "CarryArm.h"
#include "Box.h"

class SolskjærController
{
public:
	SolskjærController();
	~SolskjærController();
	void update(DWORD dt);
	void render(DWORD dt);
	void generateCarryArm(DWORD dt);

private:
	BarrierSystem* barrier;
	Solskjær* solskjær;
	CarryArm* carryArm;
	Box* tempBoxLeft;
	Box* tempBoxRight;

	int counterCarryArm;
};

