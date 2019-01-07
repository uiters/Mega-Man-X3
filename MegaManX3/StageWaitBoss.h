#pragma once
#include "Stage.h"

class StageWaitBoss : public Stage
{
private:
	Gate* gateLeft;
	Gate* gateRight;

public:
	StageWaitBoss();
	~StageWaitBoss();

public:
	void getStaticObjects(unordered_map<int, GameObject*> *saticObjects);
	void getDynamicObjects(unordered_map<int, GameObject*> *dynamicObjects);

public:
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void reset();
};

