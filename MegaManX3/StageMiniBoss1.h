#pragma once
#include "Stage.h"
#include "Genjibo.h"
#include "Shurikein.h"
class StageMiniBoss1 : public Stage
{
private:
	Gate* gateLeft;
	Gate* gateRight;
	Genjibo* genjibo;
	Shurikein* shurikein;
public:
	StageMiniBoss1();
	~StageMiniBoss1();
public:
	void getStaticObjects(unordered_map<int, GameObject*> *saticObjects);
	void getDynamicObjects(unordered_map<int, GameObject*> *dynamicObjects);

public:
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void reset();
};

