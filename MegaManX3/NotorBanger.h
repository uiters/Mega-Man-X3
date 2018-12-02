#pragma once
#include "DynamicObject.h"

#define NOTOR_BANGER_GRAVITY 0.1f
#define NOTOR_BANGER_SPEED 0.2f

#define NOTOR_BANGER_STATE_INIT 0
#define NOTOR_BANGER_STATE_SHOT 100
#define NOTOR_BANGER_STATE_READY_JUMP 200
#define NOTOR_BANGER_STATE_JUMP 300
#define NOTOR_BANGER_STATE_DIE 400

#define NOTOR_BANGER_ANI_INIT 0
#define NOTOR_BANGER_ANI_SHOT 1
#define NOTOR_BANGER_ANI_READY_JUMP 2
#define NOTOR_BANGER_ANI_JUMP 3
#define NOTOR_BANGER_ANI_DIE 4

#define NOTOR_BANGER_ID_TEXTURE 701

class NotorBanger :
	public DynamicObject
{
public:
	NotorBanger();
	NotorBanger(int id, float x, float y);
	~NotorBanger();
	void update(DWORD dt, vector<LPObject> *coObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void SetState(int state);
	void loadResources();
};

