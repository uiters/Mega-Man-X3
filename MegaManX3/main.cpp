#include "Game1.h"
#include "Camera.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow) {
	hInstanceGlobal = hInstance;
	gameGlobal = new Game1();
	keyGlobal = new KeyEvent();

	gameGlobal->init(nCmdShow);

	gameGlobal->run();
	return 0;
}