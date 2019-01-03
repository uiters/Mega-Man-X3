#pragma once
#include "Weapon.h"
#include "CTime.h"
class Bee :
	public Weapon
{
private:
	bool isSwitchDie = false;

	CTime timeDie = (8000);
	CTime timeSwitchStateDie = (6000);
	CTime timeSwitchState = (5000);
private:
	void loadResources() override;
	void(Bee::*mech)();
	unordered_map<int, GameObject*>* staticObjects;
public:
	Bee(float x, float y, float vx, float vy, bool toLeft, bool isChase);
	~Bee();
public:
	void getBoundingBox(float & left, float & top, float & right, float & bottom)override;
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	bool getIsDelete()override { return !this->visible; }

private:
	void chase();
	void fly();
	void stand();

	void switchState();
	void collisionStatic();
	void setDirection();
};

