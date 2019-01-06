#pragma once
#include "Effect.h"
class Charged1Collision :
	public Effect
{
private:
	void loadResources() override;
	static Charged1Collision* _instance;
	vector<bool> directions;
	Charged1Collision();
public:
	static Charged1Collision* getIntance();

public:
	void setDirection(bool toLeft);
	void render(DWORD dt, bool center, D3DCOLOR colorBrush = WHITE(255)) override;
	~Charged1Collision();
};

