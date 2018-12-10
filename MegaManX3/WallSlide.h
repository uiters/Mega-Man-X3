#pragma once
#include "Effect.h"
class WallSlide :
	public Effect
{
private:
	void loadResources() override;
	static WallSlide* _instance;
	WallSlide();
public:
	~WallSlide();
	static WallSlide* getInstance();
};

