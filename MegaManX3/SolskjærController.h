#pragma once
#include<vector>

#include "BarrierSystem.h"
#include "Solskjær.h"
#include "CarryArm.h"
#include "MegamanX.h"
#include <unordered_map>
class SolskjærController
{
public:
	SolskjærController();
	~SolskjærController();
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObject, MegamanX* main);
	void render(DWORD dt);
	
	void generateCarryArm(DWORD dt);
	void generateSolskjær(DWORD dt);

	bool getIsFinish() { return barrier->isFinish; }

private:
	BarrierSystem* barrier;
	Solskjær* solskjær;
	CarryArm* carryArmFirst;
	CarryArm* carryArmSecond;
	unordered_map<int, GameObject*> objects;
	unordered_map<int, GameObject*>* staticObject;
	
	bool isOnlyOne;
	bool isDisplayBoss;
	int clock;
	int clockForCarryArm;
	int clockForSolskjær;
	int limitTime;

	void collisionMain(MegamanX* main);
	void bulletCollisionDynamic(MegamanX* main);
	void dynamicCollisionMain(MegamanX* main);
};

