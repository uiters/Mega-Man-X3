#pragma once
#include "DynamicObject.h"

#define HEAD_GUNNER_STATE_DEFAULT 0
#define HEAD_GUNNER_STATE_SHOT_TOP 100
#define HEAD_GUNNER_STATE_SHOT_BOTTOM 200
#define HEAD_GUNNER_STATE_SHOT_LEFT 300 // 2 times
#define HEAD_GUNNER_STATE_SHOT_RIGHT 400

#define HEAD_GUNNER_ID_TEXTURE 702

class HeadGunner :
	public DynamicObject
{
public:
	HeadGunner();
	HeadGunner(int id, float x, float y, bool nx);
	~HeadGunner();
	void update(DWORD dt, vector<LPObject> *coObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void setState(int state);
	void loadResources();
private:
	bool nx;
};

