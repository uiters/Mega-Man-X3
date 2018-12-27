#pragma once
#include "Effect.h"
class Charged1Collision :
	public Effect
{
private:
	void loadResources() override;
	static Charged1Collision* _instance;
	Charged1Collision();
public:
	static Charged1Collision* getIntance();

public:
	~Charged1Collision();
};

