#pragma once
#include "Stage.h"
#include "BlastHornet.h"
class StageBoss : public Stage
{
private:
	Gate* gateLeft;
	BlastHornet* boss;
	HPBar* hpBarBoss;

	bool ready = false;
	bool gateLeftClose = false;
public:
	StageBoss();
	~StageBoss();


public:
	void getStaticObjects(unordered_map<int, GameObject*> *saticObjects);
	void getDynamicObjects(unordered_map<int, GameObject*> *dynamicObjects);

public:
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void reset();

public:
	HPBar* getHPBar() { if (ready && !main->isRevivaling) return hpBarBoss; else return null; }
	HornetPoint* getHornetPoint() { if (boss->isDeath() && !main->isRevivaling) return null; else return boss->getHoretPoint(); }
};

