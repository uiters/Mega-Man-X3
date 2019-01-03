#pragma once
#include "Effect.h"
class BeeExplosion :
	public Effect
{
private:
	void loadResources() override;
	static BeeExplosion* _instance;
	BeeExplosion();
public:
	~BeeExplosion();
public:
	static BeeExplosion* getInstance();
};

