#pragma once
#include "StaticObject.h"
class Brick
	:public StaticObject
{
public:
	Brick(UINT id, int x, int y, int width, int height);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	void drawLine(LPDIRECT3DDEVICE9 Device_Interface, int x, int y, D3DCOLOR color);
	~Brick();

};

