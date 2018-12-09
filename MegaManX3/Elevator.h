#pragma once
#include "DynamicObject.h"
class Elevator :
	public DynamicObject
{
private:
	void loadResources() override {};
	Elevator* clone(int id, int x, int y) override { return nullptr; }
public:
	Elevator(UINT idTexture, float x, float y);
	~Elevator();
	
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects = 0, unordered_map<int, CTreeObject*>* dynamicObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
};

