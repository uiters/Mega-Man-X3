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
	spritesGlobal->addSprite(Hornet_Explosion + 1, TBlastHornet, 123, 233, 32, 32);
	spritesGlobal->addSprite(Hornet_Explosion + 2, TBlastHornet, 159, 226, 28, 24);
	spritesGlobal->addSprite(Hornet_Explosion + 3, TBlastHornet, 192, 224, 30, 27);
	spritesGlobal->addSprite(Hornet_Explosion + 4, TBlastHornet, 230, 223, 32, 27);
	spritesGlobal->addSprite(Hornet_Explosion + 5, TBlastHornet, 269, 220, 32, 30);
	spritesGlobal->addSprite(Hornet_Explosion + 6, TBlastHornet, 312, 220, 32, 30);
	spritesGlobal->addSprite(Hornet_Explosion + 7, TBlastHornet, 352, 220, 32, 30);

	// Drop bee
	spritesGlobal->addSprite(Hornet_Drop_Bee, TBlastHornet, 263, 6, 51, 62);
	spritesGlobal->addSprite(Hornet_Drop_Bee + 1, TBlastHornet, 320, 6, 48, 67);
	spritesGlobal->addSprite(Hornet_Drop_Bee + 2, TBlastHornet, 377, 5, 47, 72);
	spritesGlobal->addSprite(Hornet_Drop_Bee + 3, TBlastHornet, 429 - 2, 4, 47 + 2, 72);
	spritesGlobal->addSprite(Hornet_Drop_Bee + 4, TBlastHornet, 482, 6, 47, 72);

	//wing
	spritesGlobal->addSprite(Hornet_Wing, TBlastHornet, 417, 154, 96, 41);
	spritesGlobal->addSprite(Hornet_Wing + 1, TBlastHornet, 426, 203, 79, 41);
	spritesGlobal->addSprite(Hornet_Wing + 2, TBlastHornet, 444, 250, 47, 41);

	//bee type 1
	spritesGlobal->addSprite(Hornet_Bee_Type_1, TBlastHornet, 17, 172, 19, 22);
	spritesGlobal->addSprite(Hornet_Bee_Type_1 + 1, TBlastHornet, 41, 176, 19, 18);
	//type 2
	spritesGlobal->addSprite(Hornet_Bee_Type_2, TBlastHornet, 64, 174, 22, 20);

	//bee die_1
	spritesGlobal->addSprite(Hornet_Bee_Die_1, TBlastHornet, 17, 198, 19, 22);
	spritesGlobal->addSprite(Hornet_Bee_Die_1 + 1, TBlastHornet, 41, 202, 19, 18);

	//bee die_2
	spritesGlobal->addSprite(Hornet_Bee_Die_2, TBlastHornet, 64, 200, 22, 20);

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
	spritesGlobal->addSprite(Hornet_Aimming + 1, TBlastHornet, 158, 186, 23, 23);

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
	ani->add(Hornet_Prepare_Prick + 5, 10000);
	_animations[Hornet_Prick] = ani;

	//drop bee
	ani = new CAnimation(200);
	ani->add(Hornet_Stand, 300);
	for (int i = 0; i < 5; ++i)
	{
		ani->add(Hornet_Drop_Bee + i);
	}
	_animations[Hornet_Drop_Bee] = ani;

	
	ani = new CAnimation(40);
	ani->add(Hornet_Wing);
	ani->add(Hornet_Wing + 1);
	ani->add(Hornet_Wing + 2);
	_animations[Hornet_Wing] = ani;

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
