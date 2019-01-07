#pragma once
#include "ConstGlobals.h"
#include "GameObject.h"
#include "Camera.h"
class Stage
{
public:
	Stage();
	~Stage();

public:
	virtual void getStaticObjects(unordered_map<int, GameObject*> *saticObjects) = 0;
	virtual void getDynamicObjects(unordered_map<int, GameObject*> *dynamicObjects) = 0;

public:
	virtual void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects) = 0;
	virtual void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) = 0;
	virtual void reset() = 0;
};

