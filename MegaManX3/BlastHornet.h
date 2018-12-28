#pragma once
#include "DynamicObject.h"
class BlastHornet :
	public DynamicObject
{
private:
	void loadResources() override;
public:
	BlastHornet();
	~BlastHornet();

public:
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
};

