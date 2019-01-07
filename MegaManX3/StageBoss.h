#pragma once
#include "Stage.h"
#include "BlastHornet.h"
class StageBoss : public Stage
{
private:
	Gate* gate;
	BlastHornet* boss;
	HPBar* hpBarBoss;
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
	HPBar* getHPBar() { return hpBarBoss; }
};

