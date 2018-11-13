#pragma once
#include "Game.h"

#include "ScenceController.h"
#include "Camera.h"
class Game1 :
	public Game
{
	ScenceController* control;
public:
	void initGolbals() override; // call first
	void loadResource() override; // 2
	void initOption() override; // 3
	void update(DWORD) override;
	void render(DWORD) override;
	
	~Game1();
};

