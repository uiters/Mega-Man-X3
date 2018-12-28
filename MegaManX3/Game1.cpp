#include "Game1.h"
#include "Helit.h"
void Game1::initGolbals()
{
	texturesGlobal = CTextures::getInstance();
	spritesGlobal = CSprites::getInstance();
	animationsGlobal = CAnimations::getInstance();

	//cameraGlobal = new Camera(0, 550, CAMERA_WIDTH, CAMERA_HEIGHT);//start
	//cameraGlobal = new Camera(800, 550, CAMERA_WIDTH, CAMERA_HEIGHT);
	//cameraGlobal = new Camera(2344, 910, CAMERA_WIDTH, CAMERA_HEIGHT);
	cameraGlobal = new Camera(7715, 1681, CAMERA_WIDTH, CAMERA_HEIGHT);//boss

	viewPortGlobal = &cameraGlobal->viewport;
}

void Game1::loadResource()
{
	texturesGlobal->add(Megaman, MEGAMAN, 637, 533, D3DCOLOR_XRGB(80, 56, 72));
	texturesGlobal->add(TElevator, SHIP, 0, 0); 
	texturesGlobal->add(TDashSmoke, DASH_SMOKE, 0, 0, D3DCOLOR_XRGB(64, 102, 232));
	texturesGlobal->add(TDashSpark, DASH_SPARK, 0, 0, D3DCOLOR_XRGB(64, 102, 232));
	texturesGlobal->add(TSlide, SLIDE, 0, 0, D3DCOLOR_XRGB(64, 102, 232));
	texturesGlobal->add(TKick, KICK, 0, 0, D3DCOLOR_XRGB(64, 102, 232));
	texturesGlobal->add(TCharged1, CHARGED_SHOOT1, 0, 0, D3DCOLOR_XRGB(64, 102, 232));
	texturesGlobal->add(TCharged2, CHARGED_SHOOT2, 0, 0, D3DCOLOR_XRGB(64, 102, 232));
	texturesGlobal->add(TDeath, DIE, 135, 38, D3DCOLOR_XRGB(50, 96, 166));
	texturesGlobal->add(TChargedCollision, CHARGED_EFFECT_COLLISION, 0, 0, D3DCOLOR_XRGB(50, 96, 166));

	texturesGlobal->add(THelit, HELIT, 0 , 0 , D3DCOLOR_XRGB(255, 0, 255));
	texturesGlobal->add(TExplosion, EXPLOISION);
	texturesGlobal->add(THeadGun, HEAD_GUN, 0, 0, D3DCOLOR_XRGB(255, 0, 255));

	texturesGlobal->add(TBlastHornet, BLASTHORNET, 0, 0, D3DCOLOR_XRGB(0, 128, 128));

	//main = new MegamanX(Megaman, 100, 650);
	//main = new MegamanX(Megaman, 768, 650);
	//7715 1681
	//main = new MegamanX(Megaman, 2344, 910);
	main = new MegamanX(Megaman, 7715, 1681);
	keyGlobal = main;

	//Weapon *main_bullet = new Weapon(Megaman, main->x, main->y, 0.5, 0);
	//main->addWeapon(main_bullet);
#pragma region appear
	spritesGlobal->add(appear, Megaman, 5, 4, 13, 51);
	spritesGlobal->add(appear + 1, Megaman, 17, 23, 38, 51);
	spritesGlobal->add(appear + 2, Megaman, 43, 10, 72, 51);
	spritesGlobal->add(appear + 3, Megaman, 77, 13, 106, 51);
	spritesGlobal->add(appear + 4, Megaman, 111, 16, 141, 51);
	spritesGlobal->add(appear + 5, Megaman, 144, 18, 174, 51);
	spritesGlobal->add(appear + 6, Megaman, 179, 20, 208, 51);
	spritesGlobal->add(appear + 7, Megaman, 213, 18, 242, 51);

	auto ani = new CAnimation(1000);
	ani->add(appear, 1000);
	for (int i = 1; i < 8; i++)
	{
		ani->add(appear + i, 100);
	}
	animationsGlobal->add(appear, ani);
	main->addAnimation(appear);
#pragma endregion

#pragma region stand
	spritesGlobal->add(stand, Megaman, 213, 18, 242, 51);
	spritesGlobal->add(stand + 1, Megaman, 247, 18, 276, 51);
	spritesGlobal->add(stand + 2, Megaman, 281, 18, 310, 51);

	ani = new CAnimation(100);
	for (int i = 0; i < 3; i++)
	{
		ani->add(stand + i);
	}
	animationsGlobal->add(stand, ani);
	main->addAnimation(stand);
#pragma endregion

#pragma region run
	spritesGlobal->add(MegaManAnimation::run, Megaman, 319, 19, 348, 52);
	spritesGlobal->add(MegaManAnimation::run + 1, Megaman, 350, 19, 369, 52);
	spritesGlobal->add(MegaManAnimation::run + 2, Megaman, 371, 19, 393, 52);
	spritesGlobal->add(MegaManAnimation::run + 3, Megaman, 394, 19, 425, 52);
	spritesGlobal->add(MegaManAnimation::run + 4, Megaman, 426, 20, 459, 52);
	spritesGlobal->add(MegaManAnimation::run + 5, Megaman, 460, 20, 485, 52);
	spritesGlobal->add(MegaManAnimation::run + 6, Megaman, 489, 19, 510, 52);
	spritesGlobal->add(MegaManAnimation::run + 7, Megaman, 511, 18, 535, 52);
	spritesGlobal->add(MegaManAnimation::run + 8, Megaman, 539, 19, 568, 52);
	spritesGlobal->add(MegaManAnimation::run + 9, Megaman, 570, 20, 603, 52);
	spritesGlobal->add(MegaManAnimation::run + 10, Megaman, 604, 20, 632, 52);

	ani = new CAnimation(550);
	for (int i = 0; i < 11; i++)
	{
		ani->add(MegaManAnimation::run + i, 50);
	}
	animationsGlobal->add(MegaManAnimation::run, ani);
	main->addAnimation(MegaManAnimation::run);
#pragma endregion

#pragma region jump
	spritesGlobal->add(jump, Megaman, 5, 73, 28, 109);
	spritesGlobal->add(jump + 1, Megaman, 34, 69, 48, 109);
	spritesGlobal->add(jump + 2, Megaman, 55, 64, 73, 109);

	ani = new CAnimation(450);
	ani->add(jump, 10);
	ani->add(jump + 1, 40);
	ani->add(jump + 2, 400);
	animationsGlobal->add(jump, ani);
	main->addAnimation(jump);
#pragma endregion

#pragma region fall
	spritesGlobal->add(fall, Megaman, 77, 69, 99, 109);
	spritesGlobal->add(fall + 1, Megaman, 102, 68, 128, 109);
	spritesGlobal->add(fall + 2, Megaman, 134, 72, 157, 109);

	ani = new CAnimation(450);
	ani->add(fall, 400);
	ani->add(fall + 1, 40);
	ani->add(fall + 2, 10);
	animationsGlobal->add(fall, ani);
	main->addAnimation(fall);
#pragma endregion

#pragma region dash
	spritesGlobal->add(dash, Megaman, 278, 127, 314, 157);
	spritesGlobal->add(dash + 1, Megaman, 319, 132, 356, 157);

	ani = new CAnimation(600);
	ani->add(dash, 20);
	ani->add(dash + 1, 580);
	animationsGlobal->add(dash, ani);
	main->addAnimation(dash);
#pragma endregion

#pragma region cling
	spritesGlobal->add(cling, Megaman, 35, 211, 61, 253);

	ani = new CAnimation(100);
	ani->add(cling);
	animationsGlobal->add(cling, ani);
	main->addAnimation(cling);
#pragma endregion

#pragma region slide
	spritesGlobal->add(slide, Megaman, 64, 212, 91, 253);
	ani = new CAnimation(100);
	ani->add(slide);
	animationsGlobal->add(slide, ani);
	main->addAnimation(slide);
#pragma endregion

#pragma region enhance
	spritesGlobal->add(enhance, Megaman, 470, 118, 497, 162);
	spritesGlobal->add(enhance + 1, Megaman, 510, 118, 529, 162);
	spritesGlobal->add(enhance + 2, Megaman, 532, 115, 565, 162);
	spritesGlobal->add(enhance + 3, Megaman, 568, 118, 596, 162);
	spritesGlobal->add(enhance + 4, Megaman, 599, 118, 629, 162);

	ani = new CAnimation(100);
	for (int i = 0; i < 5; i++)
	{
		ani->add(enhance + i);
	}
	animationsGlobal->add(enhance, ani);
	main->addAnimation(enhance);
#pragma endregion

#pragma region shock
	spritesGlobal->add(shock, Megaman, 10, 316, 35, 351);
	spritesGlobal->add(shock + 1, Megaman, 39, 318, 67, 351);
	spritesGlobal->add(shock + 2, Megaman, 72, 318, 100, 351);
	spritesGlobal->add(shock + 3, Megaman, 105, 308, 136, 355);
	spritesGlobal->add(shock + 4, Megaman, 139, 318, 167, 351);
	spritesGlobal->add(shock + 5, Megaman, 172, 308, 203, 355);
	spritesGlobal->add(shock + 6, Megaman, 207, 318, 235, 351);
	spritesGlobal->add(shock + 7, Megaman, 240, 308, 271, 355);
	spritesGlobal->add(shock + 8, Megaman, 275, 318, 305, 351);
	spritesGlobal->add(shock + 8, Megaman, 309, 318, 337, 351);
	spritesGlobal->add(shock + 9, Megaman, 341, 316, 366, 351);

	ani = new CAnimation(50);
	for (int i = 0; i < 10; ++i)
	{
		ani->add(shock + i, 20);
	}
	animationsGlobal->add(shock, ani);
	main->addAnimation(shock);
#pragma endregion

#pragma region shoot
	spritesGlobal->add(shoot, Megaman, 6, 167, 35, 200);
	spritesGlobal->add(shoot + 1, Megaman, 41, 167, 69, 200);

	ani = new CAnimation(100);
	ani->add(shoot);
	ani->add(shoot + 1);
	animationsGlobal->add(shoot, ani);
	main->addAnimation(shoot);
#pragma endregion

#pragma region run_shoot
	spritesGlobal->add(run_shoot, Megaman, 290, 71, 318, 104);
	spritesGlobal->add(run_shoot + 1, Megaman, 319, 70, 350, 104);
	spritesGlobal->add(run_shoot + 2, Megaman, 351, 71, 385, 104);
	spritesGlobal->add(run_shoot + 3, Megaman, 387, 72, 424, 104);
	spritesGlobal->add(run_shoot + 4, Megaman, 426, 72, 459, 104);
	spritesGlobal->add(run_shoot + 5, Megaman, 460, 71, 490, 104);
	spritesGlobal->add(run_shoot + 6, Megaman, 491, 70, 523, 104);
	spritesGlobal->add(run_shoot + 7, Megaman, 524, 71, 557, 104);
	spritesGlobal->add(run_shoot + 8, Megaman, 560, 72, 596, 104);
	spritesGlobal->add(run_shoot + 9, Megaman, 597, 72, 630, 104);

	ani = new CAnimation(550);
	for (int i = 0; i < 10; i++)
	{
		ani->add(run_shoot + i, 50);
	}
	animationsGlobal->add(run_shoot, ani);
	main->addAnimation(run_shoot);
#pragma endregion

#pragma region jump_shoot
	spritesGlobal->add(jump_shoot, Megaman, 5, 121, 33, 157);
	spritesGlobal->add(jump_shoot + 1, Megaman, 36, 117, 59, 157);
	spritesGlobal->add(jump_shoot + 2, Megaman, 60, 112, 86, 157);

	ani = new CAnimation(600);
	ani->add(jump_shoot, 10);
	ani->add(jump_shoot + 1, 40);
	ani->add(jump_shoot + 2, 550);
	animationsGlobal->add(jump_shoot, ani);
	main->addAnimation(jump_shoot);
#pragma endregion

#pragma region dash_shoot
	spritesGlobal->add(dash_shoot, Megaman, 367, 126, 404, 156);
	spritesGlobal->add(dash_shoot + 1, Megaman, 410, 131, 458, 156);

	ani = new CAnimation(600);
	ani->add(dash_shoot, 20);
	ani->add(dash_shoot + 1, 580);
	animationsGlobal->add(dash_shoot, ani);
	main->addAnimation(dash_shoot);
#pragma endregion

#pragma region cling_shoot
	spritesGlobal->add(cling_shoot, Megaman, 46, 259, 78, 301);
	ani = new CAnimation(10);
	ani->add(cling_shoot);
	animationsGlobal->add(cling_shoot, ani);
	main->addAnimation(cling_shoot);
#pragma endregion

#pragma region slide_shoot
	spritesGlobal->add(slide_shoot, Megaman, 84, 258, 115, 299);
	ani = new CAnimation(10);
	ani->add(slide_shoot);
	animationsGlobal->add(slide_shoot, ani);
	main->addAnimation(slide_shoot);
#pragma endregion

#pragma region fall_shoot
	spritesGlobal->add(fall_shoot, Megaman, 88, 117, 118, 157);
	spritesGlobal->add(fall_shoot + 1, Megaman, 120, 116, 150, 157);
	spritesGlobal->add(fall_shoot + 2, Megaman, 152, 120, 181, 157);

	ani = new CAnimation(450);
	ani->add(fall_shoot, 400);
	ani->add(fall_shoot + 1, 40);
	ani->add(fall_shoot + 2, 10);
	animationsGlobal->add(fall_shoot, ani);
	main->addAnimation(fall_shoot);
#pragma endregion

#pragma region bullet_lv1
	spritesGlobal->add(bullet_lv1, Megaman, 5, 377, 12, 382);
	ani = new CAnimation(50);
	ani->add(bullet_lv1);
	animationsGlobal->add(bullet_lv1, ani);
#pragma endregion

#pragma region bullet_lv2
	spritesGlobal->add(bullet_lv2, Megaman, 26, 373, 39, 386);
	spritesGlobal->add(bullet_lv2 + 1, Megaman, 48, 368, 71, 391);
	spritesGlobal->add(bullet_lv2 + 2, Megaman, 82, 375, 109, 386);
	spritesGlobal->add(bullet_lv2 + 3, Megaman, 120, 376, 151, 383);
	spritesGlobal->add(bullet_lv2 + 4, Megaman, 163, 374, 200, 385);
	spritesGlobal->add(bullet_lv2 + 5, Megaman, 216, 368, 255, 386);
	spritesGlobal->add(bullet_lv2 + 6, Megaman, 265, 368, 300, 389);
	ani = new CAnimation(900);
	ani->add(bullet_lv2 + 0, 20);
	ani->add(bullet_lv2 + 1, 30);
	ani->add(bullet_lv2 + 2, 60);
	ani->add(bullet_lv2 + 3, 70);
	ani->add(bullet_lv2 + 4, 130);
	ani->add(bullet_lv2 + 5, 500);
	ani->add(bullet_lv2 + 6, 100);
	animationsGlobal->add(bullet_lv2, ani);
#pragma endregion

#pragma region bullet_lv3
	spritesGlobal->add(bullet_lv3, Megaman, 35, 496, 80, 526);
	spritesGlobal->add(bullet_lv3 + 1, Megaman, 87, 496, 131, 524);
	spritesGlobal->add(bullet_lv3 + 2, Megaman, 146, 495, 187, 525);
	ani = new CAnimation(900);
	ani->add(bullet_lv3, 100);
	ani->add(bullet_lv3 + 1, 300);
	ani->add(bullet_lv3 + 2, 500);

	animationsGlobal->add(bullet_lv3, ani);
#pragma endregion

	main->state = appear;


#pragma region Elevator

	spritesGlobal->addSprite(Elevator1, TElevator, 0, 0, 96, 45);
	spritesGlobal->addSprite(Elevator2, TElevator, 0, 45, 96, 45);
	spritesGlobal->addSprite(Elevator3, TElevator, 0, 91, 96, 45);


	ani = new CAnimation(40);
	ani->add(Elevator1);
	ani->add(Elevator2);
	ani->add(Elevator3);

	animationsGlobal->add(TElevator, ani);
#pragma endregion

#pragma region preDie
	spritesGlobal->add(preDie, TDeath, 77, 1, 102, 36);
	spritesGlobal->add(preDie + 1, TDeath, 107, 1, 132, 36);
	ani = new CAnimation(1000);
	ani->add(preDie, 50);
	ani->add(preDie + 1, 100);
	animationsGlobal->add(preDie, ani);
	main->addAnimation(preDie);
#pragma endregion

#pragma region die
	for (int i = 0; i < 5; i++)
	{
		spritesGlobal->add(die + i, TDeath, i * 15 + 1, 0, (i + 1) * 15, 14);
	}
	ani = new CAnimation(750);
	for (int i = 0; i < 5; ++i)
	{
		ani->add(die + i, 150);
	}
	animationsGlobal->add(die, ani);
	main->addAnimation(die);
#pragma endregion
	
#pragma region Headgun
	spritesGlobal->addSprite(bullet_head_gun_state_default, THeadGun, 71, 13, 7, 7);
	spritesGlobal->addSprite(bullet_head_gun_state_2, THeadGun, 33, 13, 23, 7);
	spritesGlobal->addSprite(bullet_head_gun_state_2 + 1, THeadGun, 8, 13, 23, 7);

	//default
	ani = new CAnimation(200);
	ani->add(bullet_head_gun_state_default);
	animationsGlobal->add(bullet_head_gun_state_default, ani);

	//state_2
	ani = new CAnimation(50);
	ani->add(bullet_head_gun_state_2);
	ani->add(bullet_head_gun_state_2 + 1);
	animationsGlobal->add(bullet_head_gun_state_2, ani);
#pragma endregion

}


void Game1::initOption()
{
	mainGlobal = main;
	auto x = Factory::getInstance()->createObjects(OBJECT_TXT);
	root = Factory::getInstance()->createQuadTree(QUADTREE_TXT, *x);
	auto rootdyanamic = Factory::getInstance()->createQuadTree(QUADTREE_DYNAMIC_TXT, *x);
	delete x;
	controller = new Controller(main, root, rootdyanamic);
	Weapon::setWeaponEffect(WeaponEffectController::getIntance());

}

void Game1::update(DWORD dt)
{
	
	keyGlobal->processKeyboard();
	controller->update(dt);	
	cameraGlobal->update(main->x, main->y);
}	

void Game1::render(DWORD dt)
{
	controller->render(dt);
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