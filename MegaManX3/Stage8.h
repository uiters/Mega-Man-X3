#pragma once
#include "Stage.h"
class Stage8 :
	public Stage
{
private:
	Gate* gateLeft;
	Gate* gateRight;
	bool drawLeft;
	bool drawRight;
	bool ready;
	bool gateLeftClose;
public:
	Stage8();
	~Stage8();

public:
	void getStaticObjects(unordered_map<int, GameObject*> *saticObjects);
	void getDynamicObjects(unordered_map<int, GameObject*> *dynamicObjects);

public:
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void reset();
};

