#pragma once
#include "Stage.h"

class StageByte : public Stage
{
private:
	Gate* gateLeft;
	Gate* gateRight;
	bool ready;
	bool gateLeftClose;
public:
	StageByte();
	~StageByte();
public:
	void getStaticObjects(unordered_map<int, GameObject*> *saticObjects);
	void getDynamicObjects(unordered_map<int, GameObject*> *dynamicObjects);

public:
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void reset();
};

