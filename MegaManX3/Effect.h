#pragma once
#include "GameObject.h"
class Effect :
	public GameObject
{
private:
	bool finish = false;
	int loop = 0;
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override {};
public:

	Effect(int idTexture, int x, int y, int loop);
	~Effect();

	
	virtual void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) = 0;
};

