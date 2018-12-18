#include "BulletCollision.h"


BulletCollision::BulletCollision()
{
	loadResources();
}

BulletCollision::~BulletCollision()
{
}


void BulletCollision::loadResources()
{
	CTextures * textures = CTextures::getInstance();

	if (textures->getTexture(BULLET_COLLISION_ID_TEXTURE) == NULL)
		textures->add(BULLET_COLLISION_ID_TEXTURE, L"Resource\\Textures\\effect2.png", 0, 0, D3DCOLOR_XRGB(255, 255, 255));

	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();

	auto ani =  new AnimationOneTime(50);

	// default
	sprites->addSprite(10011, BULLET_COLLISION_ID_TEXTURE, 9, 15, 32, 32);
	sprites->addSprite(10012, BULLET_COLLISION_ID_TEXTURE, 41, 15, 32, 32);
	sprites->addSprite(10013, BULLET_COLLISION_ID_TEXTURE, 79, 15, 32, 32);
	sprites->addSprite(10014, BULLET_COLLISION_ID_TEXTURE, 112, 15, 32, 32);
	sprites->addSprite(10015, BULLET_COLLISION_ID_TEXTURE, 151, 15, 32, 32);
	sprites->addSprite(10016, BULLET_COLLISION_ID_TEXTURE, 192, 15, 32, 32);
	sprites->addSprite(10017, BULLET_COLLISION_ID_TEXTURE, 233, 13, 32, 32);
	sprites->addSprite(10018, BULLET_COLLISION_ID_TEXTURE, 272, 13, 32, 32);

	ani->add(10011);
	ani->add(10012);
	ani->add(10013);
	ani->add(10014);
	ani->add(10015);
	ani->add(10016);
	ani->add(10017);
	ani->add(10018);

	animations->add(BULLET_COLLISION_STATE_DEFAULT, ani);

	// add animations
	animation = ani;
}
BulletCollision * BulletCollision::instance = null;
BulletCollision * BulletCollision::getInstance()
{
	if (!instance) instance = new BulletCollision();
	return instance;
}

