#pragma once
#include "DynamicObject.h"
#include "MegamanX.h"
class HornetPoint :
	public DynamicObject
{
private:
	void loadResources()override;
	bool isChase = false;
	bool done = false;
public:
	HornetPoint();
	~HornetPoint();

public:
	void getBoundingBox(float & left, float & top, float & right, float & bottom)override;
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;

	void setLocation(float x, float y);
	void show();
	bool isDone() { return done; }
private:
	void chase();
	void aiming();
	void collisionMain();
};

