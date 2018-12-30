#pragma once
#include<vector>

#include "BarrierSystem.h"
#include "Solskjær.h"
#include "CarryArm.h"

class SolskjærController
{
public:
	SolskjærController();
	~SolskjærController();
	void update(DWORD dt);
	void render(DWORD dt);
	void generateCarryArm(DWORD dt);
	void generateSolskjær(DWORD dt);

private:
	BarrierSystem* barrier;
	Solskjær* solskjær;
	CarryArm* carryArmFirst;
	CarryArm* carryArmSecond;

	bool isOnlyOne_1;
	bool isOnlyOne_2;
	
	int counter;
};

