#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "ConstGlobals.h"
#include "KeyEventHander.h"
#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE 1024


class Game
{
private:
	static Game* __instance;
	HWND hWnd = 0;
	LPDIRECT3D9 d3d = 0;
	LPDIRECT3DDEVICE9 d3ddv = 0;
	LPDIRECT3DSURFACE9 backBuffer = 0;
	LPD3DXSPRITE spriteHandler = 0;

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKeyEventHandler keyHandler;
public:

	static Game* GetInstance();
	void Init(int nCmdShow);

	void InitKeyboard(LPKeyEventHandler handler);
	void ProcessKeyboard();

	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, D3DCOLOR colorBrush = WHITE(255));
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, D3DCOLOR colorBrush = WHITE(255));

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return spriteHandler; }
	int IsKeyDown(int);

	void SweptAABB(
		float ml, float mt, float mr, float mb,
		float dx, float dy,
		float sl, float st, float sr, float sb,
		float &t, float &nx, float &ny);

	Game();
	~Game();
};

