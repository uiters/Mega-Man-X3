#include "BlastHornet.h"



void BlastHornet::loadResources()
{
	//stand
	spritesGlobal->addSprite(Hornet_Stand, TBlastHornet, 6, 10, 50, 62);

	//prick
	spritesGlobal->addSprite(Hornet_Prepare_Prick, TBlastHornet, 61, 8, 43, 60);
	spritesGlobal->addSprite(Hornet_Prepare_Prick + 1, TBlastHornet, 116 - 5, 9, 38 + 5, 57);
	spritesGlobal->addSprite(Hornet_Prepare_Prick + 2, TBlastHornet, 166 - 5, 7, 39 + 5, 54);
	spritesGlobal->addSprite(Hornet_Prepare_Prick + 3, TBlastHornet, 215 - 5, 8, 39 + 5, 54);
	spritesGlobal->addSprite(Hornet_Prepare_Prick + 4, TBlastHornet, 41 - 5, 92, 39 + 5, 54);
	spritesGlobal->addSprite(Hornet_Prepare_Prick + 5, TBlastHornet, 87 - 5, 91, 39 + 5, 57);//prick
	spritesGlobal->addSprite(Hornet_Prepare_Prick + 6, TBlastHornet, 132 - 5, 92, 39 + 5, 57);
	spritesGlobal->addSprite(Hornet_Prepare_Prick + 7, TBlastHornet, 178 - 5, 93, 39 + 5, 57);
	spritesGlobal->addSprite(Hornet_Prepare_Prick + 8, TBlastHornet, 222 - 1, 93, 43 + 1, 57);
	spritesGlobal->addSprite(Hornet_Prepare_Prick + 9, TBlastHornet, 272 - 4, 94, 40 + 4, 57);
	spritesGlobal->addSprite(Hornet_Prepare_Prick + 10, TBlastHornet, 315 - 1, 94, 43 + 4, 57);
	spritesGlobal->addSprite(Hornet_Prepare_Prick + 11, TBlastHornet, 364, 94, 44, 58);

	//die
	spritesGlobal->addSprite(Hornet_Die, TBlastHornet, 414, 102, 96, 48);

	//explosion
	spritesGlobal->addSprite(Hornet_Explosion, TBlastHornet, 102, 231, 16, 16);
	spritesGlobal->addSprite(Hornet_Explosion + 1, TBlastHornet, 123, 223, 32, 32);
	spritesGlobal->addSprite(Hornet_Explosion + 2, TBlastHornet, 159, 226, 28, 24);
	spritesGlobal->addSprite(Hornet_Explosion + 3, TBlastHornet, 192, 224, 30, 27);
	spritesGlobal->addSprite(Hornet_Explosion + 4, TBlastHornet, 230, 223, 32, 27);
	spritesGlobal->addSprite(Hornet_Explosion + 5, TBlastHornet, 269, 220, 32, 30);
	spritesGlobal->addSprite(Hornet_Explosion + 6, TBlastHornet, 312, 220, 32, 30);
	spritesGlobal->addSprite(Hornet_Explosion + 7, TBlastHornet, 352, 220, 32, 30);

	// Drop bee
	spritesGlobal->addSprite(Hornet_Drop_Bee_1, TBlastHornet, 263, 6, 51, 62);
	spritesGlobal->addSprite(Hornet_Drop_Bee_1 + 1, TBlastHornet, 320, 6, 48, 67);
	spritesGlobal->addSprite(Hornet_Drop_Bee_1 + 2, TBlastHornet, 377, 5, 47, 72);
	spritesGlobal->addSprite(Hornet_Drop_Bee_1 + 3, TBlastHornet, 429 - 2, 4, 47 + 2, 72);
	spritesGlobal->addSprite(Hornet_Drop_Bee_1 + 4, TBlastHornet, 482, 6, 47, 72);

	//wing
	spritesGlobal->addSprite(Hornet_Wing, TBlastHornet, 417, 154, 96, 41);
	spritesGlobal->addSprite(Hornet_Wing + 1, TBlastHornet, 426, 203, 79, 41);
	spritesGlobal->addSprite(Hornet_Wing + 2, TBlastHornet, 444, 250, 47, 41);

	//bee type 1
	spritesGlobal->addSprite(Hornet_Bee_Type_1, TBlastHornet, 17 - 2, 172, 19 + 2, 22);
	spritesGlobal->addSprite(Hornet_Bee_Type_1 + 1, TBlastHornet, 41 - 2, 172, 19 + 2, 22);
	//type 2
	spritesGlobal->addSprite(Hornet_Bee_Type_2, TBlastHornet, 64, 172, 22, 22);

	//bee die_1
	spritesGlobal->addSprite(Hornet_Bee_Die_1, TBlastHornet, 17 -2, 198, 19 + 2, 22);
	spritesGlobal->addSprite(Hornet_Bee_Die_1 + 1, TBlastHornet, 41 - 2, 198, 19 + 2, 22);

	//bee die_2
	spritesGlobal->addSprite(Hornet_Bee_Die_2, TBlastHornet, 64, 198, 22, 22);

	//bee explosion
	spritesGlobal->addSprite(Hornet_Bee_Explosion, TBlastHornet, 186, 186, 16, 16);
	spritesGlobal->addSprite(Hornet_Bee_Explosion + 1, TBlastHornet, 205, 183, 20, 20);
	spritesGlobal->addSprite(Hornet_Bee_Explosion + 2, TBlastHornet, 228, 181, 24, 24);
	spritesGlobal->addSprite(Hornet_Bee_Explosion + 2, TBlastHornet, 254, 180, 26, 26);
	spritesGlobal->addSprite(Hornet_Bee_Explosion + 3, TBlastHornet, 283, 178, 32, 30);
	spritesGlobal->addSprite(Hornet_Bee_Explosion + 4, TBlastHornet, 319, 177, 32, 32);
	spritesGlobal->addSprite(Hornet_Bee_Explosion + 5, TBlastHornet, 354, 176, 34, 34);


	//aim
	spritesGlobal->addSprite(Hornet_Aim, TBlastHornet, 96, 186, 15, 15);
	spritesGlobal->addSprite(Hornet_Aim + 1, TBlastHornet, 113, 186, 15, 15);

	//aiming
	spritesGlobal->addSprite(Hornet_Aimming, TBlastHornet, 131, 182, 23, 23);
	spritesGlobal->addSprite(Hornet_Aimming + 1, TBlastHornet, 158, 182, 23, 23);

	//stand
	CAnimation* ani = new CAnimation(100);
	ani->add(Hornet_Stand, 200);
	_animations[Hornet_Stand] = ani;

	//prick
	ani = new CAnimation(100);
	ani->add(Hornet_Stand, 200);
	for (int i = 0; i < 12; ++i)
	{
		ani->add(Hornet_Prepare_Prick + i);
	}
	ani->add(Hornet_Prepare_Prick + 5, 5000);
	_animations[Hornet_Prick] = ani;

	//prick end
	ani = new CAnimation(200);
	for (int i = 5; i > -1; --i)
	{
		ani->add(Hornet_Prepare_Prick + i);
	}
	ani->add(Hornet_Stand, 5000);
	_animations[Hornet_Prick_End] = ani;

	//drop bee 1
	ani = new CAnimation(200);
	ani->add(Hornet_Stand, 300);
	for (int i = 0; i < 3; ++i)
	{
		ani->add(Hornet_Drop_Bee_1 + i);
	}
	_animations[Hornet_Drop_Bee_1] = ani;

	//drop bee 1_1
	ani = new CAnimation(200);
	ani->add(Hornet_Drop_Bee_1 + 3);
	_animations[Hornet_Drop_Bee_1_1] = ani;

	//drop bee_1 end
	ani = new CAnimation(1000);
	ani->add(Hornet_Drop_Bee_1 + 4);
	ani->add(Hornet_Drop_Bee_1 + 1);
	ani->add(Hornet_Drop_Bee_1);
	ani->add(Hornet_Stand, 5000);

	_animations[Hornet_Drop_Bee_1_End] = ani;

	//drop bee 2
	ani = new CAnimation(40);
	for (int i = 0; i < 3; ++i)
	{
		ani->add(Hornet_Prepare_Prick + i);
	}
	ani->add(Hornet_Prepare_Prick + 3, 1000);
	_animations[Hornet_Drop_Bee_2] = ani;

	//drp bee 2 end
	ani = new CAnimation(100);
	for (int i = 2; i > -1; --i)
	{
		ani->add(Hornet_Prepare_Prick + i);
	}
	ani->add(Hornet_Stand, 2000);
	_animations[Hornet_Drop_Bee_2_End] = ani;

	//swing
	ani = new CAnimation(40);
	ani->add(Hornet_Wing);
	ani->add(Hornet_Wing + 1);
	ani->add(Hornet_Wing + 2);
	_animations[Hornet_Wing] = ani;

#pragma region Bee
	//bee 1
	ani = new CAnimation(50);
	ani->add(Hornet_Bee_Type_1);
	ani->add(Hornet_Bee_Type_1 + 1);
	animationsGlobal->add(Hornet_Bee_Type_1, ani);

	//bee 2
	ani = new CAnimation(1000);
	ani->add(Hornet_Bee_Type_2);
	animationsGlobal->add(Hornet_Bee_Type_2, ani);

	//bee die 1
	ani = new CAnimation(50);
	ani->add(Hornet_Bee_Die_1);
	ani->add(Hornet_Bee_Die_1 + 1);
	animationsGlobal->add(Hornet_Bee_Die_1, ani);

	//bee die 2
	ani = new CAnimation(50);
	ani->add(Hornet_Bee_Die_2);
	animationsGlobal->add(Hornet_Bee_Die_2, ani);

	//bee explosion
	ani = new AnimationOneTime(50);
	int time = 130;
	for (int i = 0; i < 6; ++i)
	{
		ani->add(Hornet_Bee_Explosion + i, time - i * 15);
	}
	animationsGlobal->add(Hornet_Bee_Explosion, ani);
#pragma endregion

#pragma region Aim
	ani = new CAnimation(100);
	ani->add(Hornet_Aim);
	ani->add(Hornet_Aim + 1);
	_animations[Hornet_Aim] = ani;

	ani = new CAnimation(100);
	ani->add(Hornet_Aimming);
	ani->add(Hornet_Aimming + 1);
	_animations[Hornet_Aimming] = ani;
#pragma endregion

	//bee explosion
	ani = new AnimationOneTime(50);
	time = 120;
	for (int i = 0; i < 8; ++i)
	{
		ani->add(Hornet_Explosion + i, time - i * 12);
	}
	animationsGlobal->add(Hornet_Explosion, ani);

	_animations[Hornet_Explosion] = ani;

	//bee die
	ani = new CAnimation(5000);
	ani->add(Hornet_Die);
	_animations[Hornet_Die] = ani;


	state = Hornet_Prick;
}

BlastHornet::BlastHornet()
{
	x = 7863;
	y = 1585;
	loadResources();
}


BlastHornet::~BlastHornet()
{
}

void BlastHornet::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
}

void BlastHornet::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (_death)
	{
		//effectExplosion->render(dt, true);
		return;
	}
	auto pos = cameraGlobal->transform(x, y);
	
	_animations[Hornet_Wing]->render(pos.x + 27, pos.y - 2, true);
	_animations[state]->render(pos.x, pos.y);


}

void BlastHornet::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
}
