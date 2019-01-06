#pragma once
#include "Effect.h"
class BusterCollision :
	public Effect
{
private:
	BusterCollision();
	void loadResources() override;
	static BusterCollision* _instance;
public:
	static BusterCollision* getIntance();
	~BusterCollision();
};

