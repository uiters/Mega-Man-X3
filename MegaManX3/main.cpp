#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Game.h"
#include "ConstColor.h"
#include "KeyEvent.h"
#include "Sprite.h"

#define CLASS_NAME L"MegaManX3"
#define TITLE L"Mega Man X3"

#define HLOGO L"icon.ico"
#define MAP L"map1.log"

#define WD_WIDTH 1240
#define WD_HEIGHT 700


Game *game;
KeyEvent *key;

void LoadResource() {
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	//code here--------------------------------------



	//------------------------------------------------
}

void Update(DWORD timeNow) {
	//code here--------------------------------------



	//------------------------------------------------
}

void Render(DWORD timeNow) {
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 backBuffer = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(backBuffer, NULL, WHITE(255));
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		//code here--------------------------------------



		//------------------------------------------------
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void Run() {
	MSG msg;
	int done = 0;
	DWORD timeStart = GetTickCount();
	DWORD timePerFarme = 16;
	while (!done) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		DWORD dt = now - timeStart;
		if (dt >= timePerFarme) {
			timeStart = now;
			//game->ProcessKeyboard(); key

			//code here--------------------------------------



			//------------------------------------------------
			Update(dt);
			Render(dt);
		}
		else
			Sleep(timePerFarme - dt);
	}
}

HRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow) {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	//wc.hIcon = 0;//LoadIcon(0, MB_ICONINFORMATION);
	HICON icon = (HICON)LoadImage(NULL, HLOGO, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hIcon = icon;//
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = icon;// LoadIcon(0, IDI_QUESTION);


	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(CLASS_NAME, TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WD_WIDTH, WD_HEIGHT, NULL, NULL, hInstance, NULL);

	if (!hWnd) return 0;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return hWnd;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow);
	//SetWindowPos(hWnd, 0, 0, 0, WD_WIDTH * 2, WD_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	game = Game::GetInstance();
	game->Init(hWnd);
	LoadResource();

	//key = new KeyEvent(brick[0]); //key
	//game->InitKeyboard(key); //key

	Run();
	return 0;
}