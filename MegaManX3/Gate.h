#pragma once
#include "StaticObject.h"
class Gate :
	public StaticObject
{
private:
	void loadResources() override;
	bool gateBoss;
public:
	Gate(int x, int y, int width, int height, bool gateBoss);
	~Gate();

public:
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));

};

