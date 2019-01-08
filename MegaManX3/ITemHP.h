#pragma once
#include "StaticObject.h"
#include "CTime.h"
#include "AnimationOneTime.h"
class ITemHP :
	public StaticObject
{
private:
	CAnimation* ani;
	bool isStand = false;
	int initHP;
	int width, height;
public:
	bool getIsDelete() { return !visible; }

public:
	ITemHP(float x, float y, bool isBig);
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0);
	void checkCollisionStatic(unordered_map<int, GameObject*>* staticObjects);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	~ITemHP();
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
public:
	static ITemHP* tryCreateITemHP(float x, float y);
};

