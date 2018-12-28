#pragma once

#include "DynamicObject.h";
#include "ConstGlobals.h"
#include "Camera.h"
#include "CollisionEvent.h"
#include "Brick.h"

#define SOLSKJÆR_STATE_INIT 0
#define SOLSKJÆR_STATE_READY_SHOT 100
#define SOLSKJÆR_STATE_SHOT 200
#define SOLSKJÆR_STATE_EXIT 300
#define SOLSKJÆR_STATE_DIE 400

#define SOLSKJÆR_ID_TEXTURE 791

class Solskjær :
	public DynamicObject
{
public:
	bool isRepeat;
	bool isRender;

	Solskjær();
	~Solskjær();
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void renderDie(DWORD dt, D3DCOLOR colorBrush = WHITE(255));// **
	void generatePosition();// **
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	Solskjær* clone(int id, int x, int y) override;

private:
	PointF die[3];// **

	void setState(int state);
	void loadResources();
};

