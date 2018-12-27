#pragma once
#include "Effect.h"
class Charged2Collision :
	public Effect
{
private:
	Charged2Collision();
	void loadResources() override;
	static Charged2Collision* _instance;
public:
	static Charged2Collision* getIntance();
	
	~Charged2Collision();
};

