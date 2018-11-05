#include "Game1.h"
#include "Camera.h"
#include "CKey.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow) {
	hInstanceGlobal = hInstance;

	gameGlobal = new Game1();

	gameGlobal->init(nCmdShow);

	gameGlobal->run();
	return 0;
}