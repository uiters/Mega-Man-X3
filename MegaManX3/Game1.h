#pragma once
#include "Game.h"

#include "Camera.h"
#include "Graphics.h"
#include "Animation.h"
#include "Textures.h"
#include "Sprites.h"
#include "MegamanX.h"
class Game1 :
	public Game
{

public:
	void initGolbals() override; // call first
	void loadResource() override; // 2
	void initOption() override; // 3
	void update(DWORD) override;
	void render(DWORD) override;
	
	~Game1();
};

