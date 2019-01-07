#pragma once
#include "DynamicObject.h"
#include "Shurikein.h"
class Shurikein;
class Genjibo :
	public DynamicObject
{
private:
	Shurikein * obj;
public:
	CTime timeWaiting = (2000);
	bool dropShurikein = false;
	Genjibo();
	~Genjibo();
	void loadResources() override;
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	Genjibo(UINT id, float x = 0, float y = 0, float vx = 0, float vy = 0);

public:
	void setShurikein(Shurikein *obj);
};

