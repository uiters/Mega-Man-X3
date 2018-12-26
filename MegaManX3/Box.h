#pragma once
#include "DynamicObject.h"
#include "Camera.h"

#define BOX_SPEED_X 0.04f;
#define BOX_SPEED_Y 0.04f;

#define BOX_STATE_DEFAULT 0
#define BOX_STATE_HIGHTLIGHT 100
#define BOX_STATE_DIE 200

#define BOX_ID_TEXTURE 734

class Box :
	public DynamicObject
{
public:
	bool isNext;
	bool isLeft;

	Box(int id, float x, float y);
	~Box();
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void renderDie(DWORD dt, D3DCOLOR colorBrush = WHITE(255));// **
	void generatePosition();// **
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	Box* clone(int id, int x, int y) override;

private:
	PointF die[4];// **

	void setState(int state);
	void loadResources();
};

