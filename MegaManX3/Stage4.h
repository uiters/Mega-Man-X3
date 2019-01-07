#pragma once
#include "Stage.h"
#include "Gate.h"
#include "ConstGlobals.h"
class Stage4 :
	public Stage
{
private:
	Gate* gate;
	CRectangle gateBox;
	bool draw = false;
public:
	Stage4();
	~Stage4();

public:
	void getStaticObjects(unordered_map<int, GameObject*> *saticObjects);
	void getDynamicObjects(unordered_map<int, GameObject*> *dynamicObjects);

public:
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void reset();
};

