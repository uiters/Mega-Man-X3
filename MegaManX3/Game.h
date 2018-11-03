#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "ConstGlobals.h"
#include <dinput.h>

class Game
{
protected:
	LPDIRECT3D9 d3d = 0;
	LPDIRECT3DDEVICE9 d3ddv = 0;
	LPDIRECT3DSURFACE9 backBuffer = 0;
	LPD3DXSPRITE spriteHandler = 0;

	void superRender(DWORD);

public:
	void init(int nCmdShow);
	void initGolbals();
	void run();

	LPDIRECT3DDEVICE9 getDirect3DDevice();
	LPDIRECT3DSURFACE9 getBackBuffer();
	LPD3DXSPRITE getSpriteHandler();

	virtual ~Game() {};

public:
	virtual void loadResource() = 0;
	virtual void initOption() = 0;
	virtual void update(DWORD) = 0;
	virtual void render(DWORD) = 0;
};

