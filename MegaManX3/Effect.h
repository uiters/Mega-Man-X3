#pragma once
#include "GameObject.h"
class Effect :
	public GameObject
{
private:
	bool finish = false;
public:

	Effect(int idTexture, int x, int y, bool runOnlyOne);
	~Effect();

	void getBoundingBox(float & left, float & top, float & right, float & bottom) override {};
	virtual void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) = 0;
};

