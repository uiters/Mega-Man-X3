#include "StageBoss.h"



StageBoss::StageBoss()
{
	gate = new Gate(7680, 1664, 16, 48, true);
	gate->state = GateOpen;
	boss = new BlastHornet();
	hpBarBoss = new HPBar(*boss->getHp(), 64.0f, 2.0f, false);
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
	boss->update(dt, staticObjects);
}

void StageBoss::render(DWORD dt, D3DCOLOR colorBrush)
{
	gate->render(dt);

}

void StageBoss::reset()
{
	gate->state = GateOpen;
	boss->reset();
}
