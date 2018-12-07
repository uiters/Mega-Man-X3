#pragma once
#include "DynamicObject.h"
class HeadGunner :
	public DynamicObject
{
public:
	HeadGunner();
	HeadGunner(int id, float x, float y);
	~HeadGunner();
	void update(DWORD dt, vector<LPObject> *coObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void setState(int state);
	void loadResources();
};

