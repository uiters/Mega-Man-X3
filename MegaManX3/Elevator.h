#pragma once
#include "StaticObject.h"
#include "ConstGlobals.h"
#include "Camera.h"
class Elevator :
	public StaticObject
{
private:
	void loadResources() override;
	bool isRun = false;
public:
	Elevator(UINT idTexture, float x, float y);
	~Elevator();
	
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects = 0, unordered_map<int, CTreeObject*>* dynamicObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void run();
};

