#pragma once
#include <cstdlib>
#include <ctime>

#include "DynamicObject.h";
#include "ConstGlobals.h"
#include "Camera.h"
#include "CollisionEvent.h"
#include "Brick.h"

#include "Box.h"

#define CARRY_ARM_SPEED_X 0.04f
#define CARRY_ARM_SPEED_Y 0.04f

#define CARRY_ARM_STATE_FLY 0
#define CARRY_ARM_STATE_PUT_BOX 100
#define CARRY_ARM_STATE_INJURE 200
#define CARRY_ARM_STATE_DESTROY 300
#define CARRY_ARM_STATE_DIE 400

#define CARRY_ARM_ID_TEXTURE 787

class CarryArm :
	public DynamicObject
{
public:
	float putBoxX;
	float putBoxY;
	bool isDie;
	bool isComplete;
	bool isPutBox;
	bool isLeft;
	bool isNext;

	CarryArm(float x, float y, bool isNext);
	~CarryArm();
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void renderDamage(DWORD dt, D3DCOLOR colorBrush = WHITE(255));// **
	void generatePosition();// **
	void renderDie(DWORD dt, D3DCOLOR colorBrush = WHITE(255));// **
	void generatePosition2();// **
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	CarryArm* clone(int id, int x, int y) override;

private:
	float initX;
	float initY;
	float vx;
	float vy;
	int counter;
	bool isSwitch;
	bool isDamage;
	bool isInjure;

	Box* box;
	PointF damage[10];// **
	PointF die[10];// **

	void setState(int state);
	void loadResources();
};

