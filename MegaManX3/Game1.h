#pragma once
#include "Game.h"

#include "Camera.h"
#include "MegamanX.h"
#include "Factory.h"
#include "Animation.h"
#include "CollisionEvent.h"
#include "CTreeObject.h"
#include "ConstGlobals.h"
#include "Controller.h"

#include "NotorBanger.h"
#include "HeadGunner.h"
#include "Shurikein.h"

class Game1 :
	public Game
{
	QNode* root;
	MegamanX* main;
	Controller* controller;
	NotorBanger* notorBanger;
	HeadGunner* headGunner;
	Shurikein* shurikein;
public:
	void initGolbals() override; // call first
	void loadResource() override; // 2
	void initOption() override; // 3
	void update(DWORD) override;
	void render(DWORD) override;
	
	~Game1();
};

