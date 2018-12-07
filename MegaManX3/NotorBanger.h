#pragma once
#include "DynamicObject.h";
#include "CTime.h";

#define NOTOR_BANGER_GRAVITY 0.002f
#define NOTOR_BANGER_SPEED_X 0.075f
#define NOTOR_BANGER_SPEED_Y 0.15f

#define NOTOR_BANGER_STATE_INIT 0
#define NOTOR_BANGER_STATE_SHOT_SMALL 100
#define NOTOR_BANGER_STATE_SHOT_MEDIUM 200
#define NOTOR_BANGER_STATE_SHOT_LARGE 300
#define NOTOR_BANGER_STATE_READY_JUMP_SMALL 400
#define NOTOR_BANGER_STATE_READY_JUMP_MEDIUM 500
#define NOTOR_BANGER_STATE_READY_JUMP_LARGE 600
#define NOTOR_BANGER_STATE_JUMP 700
#define NOTOR_BANGER_STATE_TOUCH_FLOOR 800
#define NOTOR_BANGER_STATE_DIE 900

#define NOTOR_BANGER_ID_TEXTURE 701

class NotorBanger : public DynamicObject
{
public:
	NotorBanger();
	NotorBanger(int id, float x, float y, bool nx, int distance);
	~NotorBanger();
	void update(DWORD dt, vector<LPObject> *coObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void setState(int state);
	void loadResources();
private:
	bool nx;
	int distance; // 0: small, 1: medium, 2: large
};

