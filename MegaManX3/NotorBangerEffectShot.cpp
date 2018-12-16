#include "NotorBangerEffectShot.h"


NotorBangerEffectShot::NotorBangerEffectShot(float x, float y)
{
	this->x = x;
	this->y = y;
}

NotorBangerEffectShot::~NotorBangerEffectShot()
{
}

void NotorBangerEffectShot::render(DWORD dt, D3DCOLOR colorBrush)
{
	auto center = cameraGlobal->transform(this->x, this->y);
	_animations[state]->render(center.x, center.y);
}

void NotorBangerEffectShot::loadResources()
{
	CTextures * textures = CTextures::getInstance();

	if (textures->getTexture(NOTOR_BANGER_EFFECT_SHOT_ID_TEXTURE) == NULL)
		textures->add(NOTOR_BANGER_EFFECT_SHOT_ID_TEXTURE, L"Resource\\Textures\\effect1.png", 0, 0, D3DCOLOR_XRGB(255, 255, 255));

	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();

	LPANIMATION ani;

	// default
	sprites->addSprite(10001, NOTOR_BANGER_EFFECT_SHOT_ID_TEXTURE, 12, 6, 14, 14); // 14 x 14
	sprites->addSprite(10002, NOTOR_BANGER_EFFECT_SHOT_ID_TEXTURE, 25, 6, 14, 14);
	sprites->addSprite(10003, NOTOR_BANGER_EFFECT_SHOT_ID_TEXTURE, 43, 6, 14, 14);
	sprites->addSprite(10004, NOTOR_BANGER_EFFECT_SHOT_ID_TEXTURE, 8, 23, 14, 14);
	sprites->addSprite(10005, NOTOR_BANGER_EFFECT_SHOT_ID_TEXTURE, 29, 23, 14, 14);
	sprites->addSprite(10006, NOTOR_BANGER_EFFECT_SHOT_ID_TEXTURE, 49, 23, 14, 14);

	ani = new CAnimation(200);
	ani->add(10001);
	ani->add(10002);
	ani->add(10003);
	ani->add(10004);
	ani->add(10005);
	ani->add(10006);
	
	animations->add(NOTOR_BANGER_EFFECT_SHOT_STATE_DEFAULT, ani);

	// add animations
	this->addAnimation(NOTOR_BANGER_EFFECT_SHOT_STATE_DEFAULT);
}

void NotorBangerEffectShot::setState(int state)
{
	this->state = state;
}
