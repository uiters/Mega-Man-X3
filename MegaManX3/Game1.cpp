#include "Game1.h"
#include "Animation.h"

void Game1::initGolbals()
{
	texturesGlobal = CTextures::getInstance();
	spritesGlobal = CSprites::getInstance();
	animationsGlobal = CAnimations::getInstance();
	cameraGlobal = new Camera(0, 754, WD_WIDTH, WD_HEIGHT);
	viewPortGlobal = &cameraGlobal->viewport;
}

void Game1::loadResource()
{
	main = new MegamanX();
	keyGlobal = main;
}

void Game1::initOption()
{
	control = new ScenceController(1);
	node = new QNode(0, 0, 0, 0, 0);
}

void Game1::update(DWORD dt)
{
	keyGlobal->processKeyboard();
	control->update(viewPortGlobal);

}	

void Game1::render(DWORD dt)
{
	control->render(dt);
}


Game1::~Game1()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
	spriteHandler = 0;
	backBuffer = 0;
	d3ddv = 0;
	d3d = 0;
}