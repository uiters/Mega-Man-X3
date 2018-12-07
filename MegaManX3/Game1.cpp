#include "Game1.h"
#include "Animation.h"

void Game1::initGolbals()
{
	texturesGlobal = CTextures::getInstance();
	spritesGlobal = CSprites::getInstance();
	animationsGlobal = CAnimations::getInstance();
	cameraGlobal = new Camera(0, 512, 256, 222);
	cameraGlobal->setSizeWorld(2304, 1024);
	viewPortGlobal = &cameraGlobal->viewport;
}

void Game1::loadResource()
{
	main = new MegamanX();
	keyGlobal = main;

	notorBanger = new NotorBanger();
	notorBanger->loadResources();
	notorBanger->setState(NOTOR_BANGER_STATE_INIT);

	headGunner = new HeadGunner();
	headGunner->loadResources();
	headGunner->setState(HEAD_GUNNER_STATE_DEFAULT);
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
	notorBanger->update(dt);
	headGunner->update(dt);
	//cameraGlobal->update
}	

void Game1::render(DWORD dt)
{
	control->render(dt);
	notorBanger->render(dt);
	headGunner->render(dt);
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