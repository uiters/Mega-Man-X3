#pragma once
#include "DynamicObject.h"
#include "Camera.h"

#define HEAD_GUNNER_STATE_DEFAULT 0
#define HEAD_GUNNER_STATE_SHOT_TOP 100
#define HEAD_GUNNER_STATE_SHOT_BOTTOM 200
#define HEAD_GUNNER_STATE_SHOT_LEFT 300 // 2 times
#define HEAD_GUNNER_STATE_SHOT_RIGHT 400
#define HEAD_GUNNER_STATE_DIE 500

#define HEAD_GUNNER_ID_TEXTURE 702

class HeadGunner :
	public DynamicObject
{
public:
	HeadGunner();
	HeadGunner(int id, float x, float y, bool nx);
	~HeadGunner();
	void update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects = 0, unordered_map<int, CTreeObject*>* dynamicObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void setState(int state);

public:
	HeadGunner* clone(int id, int x, int y) override;
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void loadResources() override;
private:
	bool nx;
};

