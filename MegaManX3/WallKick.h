#pragma once
#include "Effect.h"
class WallKick :
	public Effect
{
private:
	void loadResources() override;
	WallKick();
	static WallKick* _instance;
public:
	~WallKick();
	static WallKick* getInstance();
};

