#pragma once
#include "Effect.h"
class ExplosionEffect :
	public Effect
{
private:
	void loadResources() override;
	static ExplosionEffect* _instance;
	ExplosionEffect();
public:
	static ExplosionEffect* getInstance();
	~ExplosionEffect();
};

