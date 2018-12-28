#pragma once
#include "DynamicObject.h"
#include "Camera.h"

#include "CarryArm.h"
#include "Solskjær.h"

#define BARRIER_SYSTEM_SPEED_PART_1 0.03f
#define BARRIER_SYSTEM_SPEED_PART_2 0.02f

#define BARRIER_SYSTEM_STATE_PART_1 0
#define BARRIER_SYSTEM_STATE_PART_2 100

#define BARRIER_SYSTEM_ID_TEXTURE 753

class BarrierSystem :
	public DynamicObject
{
public:
	bool isHidden;

	BarrierSystem();
	~BarrierSystem();
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	BarrierSystem* clone(int id, int x, int y) override;
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;

private:
	float initX;
	float initY;

	CarryArm* carryArm;
	Solskjær* solskjær;

	void setState(int state);
	void loadResources() override;
};

