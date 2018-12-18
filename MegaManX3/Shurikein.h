#pragma once
#include "DynamicObject.h"
#include "CTime.h"
class Shurikein :
	public DynamicObject
{
public:
	bool jumped = false;
	CTime countManifest = CTime(2500);
	CTime countTimeJump = CTime(400);
	CTime countTimeFall = CTime(400);
	CTime countTimeSpin = CTime(2400);
	CTime mech1 = CTime(3000); //goAround
	CTime mech2 = CTime(2000); //rollAndJump
	CTime mech3 = CTime(2400); //spinAndJump
	Shurikein();
	~Shurikein();
	Shurikein(UINT idTexture, float x = 0, float y = 0, float vx = 0, float vy = 0);
	void loadResources() override;
	Shurikein* clone(int id, int x, int y);
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0) override;
	void collisionStatic(unordered_map<int, GameObject*>* staticObjects);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void goAround();
	void rollAndJump();
	void spinAndJump();
};

