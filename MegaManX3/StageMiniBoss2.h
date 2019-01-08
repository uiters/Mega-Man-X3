#pragma once
#include "Stage.h"
#include "SolskjærController.h"
class StageMiniBoss2 : public Stage
{
private:
	SolskjærController* boss;
	Gate* gateLeft;
	Gate* gateRight;

	bool miniBoss;
	bool doneMiniBoss;
	MegamanX* main;
	bool drawLeft;
	bool drawRight;
	bool ready;
	bool gateLeftClose;
public:
	StageMiniBoss2();
	~StageMiniBoss2();

public:
	void getStaticObjects(unordered_map<int, GameObject*> *saticObjects);
	void getDynamicObjects(unordered_map<int, GameObject*> *dynamicObjects);

public:
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void reset();
};

