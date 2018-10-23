

#include "Game.h"
#include "ConstColor.h"
#include "KeyEvent.h"
#include "Sprite.h"

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





int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow) {
	game = Game::GetInstance();
	game->Init(nCmdShow);
	LoadResource();



	Run();
	return 0;
}