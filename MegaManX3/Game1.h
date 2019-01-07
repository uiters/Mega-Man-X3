#pragma once
#include "Game.h"

#include "Camera.h"
#include "MegamanX.h"
#include "Factory.h"
#include "Animation.h"
#include "CollisionEvent.h"
#include "GameObject.h"
#include "ConstGlobals.h"
#include "Controller.h"
#include "Shurikein.h"

class Game1 :
	public Game
{
	int time;
	QNode* root;
	MegamanX* main;
	Controller* controller;
public:
	void initGolbals() override; // call first
	void loadResource() override; // 2
	void initOption() override; // 3
	void update(DWORD) override;
	void render(DWORD) override;
	
	~Game1();
};

