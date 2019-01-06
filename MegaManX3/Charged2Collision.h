#pragma once
#include "Effect.h"
class Charged2Collision :
	public Effect
{
private:
	Charged2Collision();
	void loadResources() override;
	static Charged2Collision* _instance;
	vector<bool> directions;
public:
	static Charged2Collision* getIntance();
	void setDirection(bool toLeft);
	void render(DWORD dt, bool center, D3DCOLOR colorBrush = WHITE(255)) override;
	~Charged2Collision();
};

