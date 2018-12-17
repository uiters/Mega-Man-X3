#pragma once
#include "Effect.h"
class ChargedExplosion :
	public Effect
{
private:
	void loadResources() override;
	ChargedExplosion();
	static ChargedExplosion* _instance;
public:
	ChargedExplosion* getInstance();
	~ChargedExplosion();
};

