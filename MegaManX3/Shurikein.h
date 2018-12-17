#pragma once
#include "DynamicObject.h"
#include "CTime.h"
class Shurikein :
	public DynamicObject
{
public:
	bool jumped = false;
	CTime countTimeJump = CTime(300);
	CTime countTimeFall = CTime(500);
	CTime countTimeSpin = CTime(1500);
	Shurikein();
	~Shurikein();
	Shurikein(UINT idTexture, float x = 0, float y = 0, float vx = 0, float vy = 0);
	void loadResources() override;
	Shurikein* clone(int id, int x, int y);
	void update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void goAround();
	void rollAndJump();
	void spinAndJump();
};

