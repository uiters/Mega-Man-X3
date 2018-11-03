#include "Game.h"
#include "ConstColor.h"
#include "KeyEvent.h"
#include "Sprites.h"
#include "Map.h"
#include "Megaman.h"
#include "Camera.h"
Game *game;
KeyEvent *key;
//Map* map;
Megaman* megaman = new Megaman();
Camera* camera = new Camera();
float width, height;

void LoadResource() {
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();

	//code here--------------------------------------
	textures->Add(0, L"map1.png");
	textures->Add(100, L"Brick.png");
	//map = new Map(megaman, textures->Get(0));
	textures->GetSize(0, width, height);
	camera->SetSize(width, 0);


	//------------------------------------------------
}

void Update(DWORD timeNow) {
	//code here--------------------------------------
	camera->Update(megaman->x);


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

		//game->Draw
		//code here--------------------------------------
		auto view = camera->Transform(megaman->x, megaman->y);
		float w, h;
		megaman->getSize(w, h);
		game->DrawFlipX(view.x, view.y, CTextures::GetInstance()->GetTexture(0), width, height);

		game->DrawFlipX(view.x, view.y, CTextures::GetInstance()->GetTexture(100), w, h);
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
			game->ProcessKeyboard();

			//code here--------------------------------------



			//------------------------------------------------
			Update(dt);
			Render(dt);
		}
		else
			Sleep(timePerFarme - dt);
	}
}

void End()
{
	
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow) {
	G_hInstance = hInstance;
	game = Game::GetInstance();
	key = new KeyEvent(megaman);
	game->Init(nCmdShow);
	LoadResource();

	game->InitKeyboard(key);
	Run();
	End();
	return 0;
}