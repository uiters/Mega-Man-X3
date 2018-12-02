#include "NotorBanger.h"
#include "ConstGlobals.h"
NotorBanger::NotorBanger()
{
	this->x = 30.0f;
	this->y = 30.0f;
	this->state = NOTOR_BANGER_STATE_JUMP;
}

NotorBanger::NotorBanger(int id, float x, float y)
{
	this->_id = id;
	this->x = x;
	this->y = y;
	this->state = NOTOR_BANGER_STATE_INIT;
}

NotorBanger::~NotorBanger()
{
}


void NotorBanger::update(DWORD dt, vector<LPObject>* coObjects)
{	
	//updateBox();

}

void NotorBanger::render(DWORD dt, D3DCOLOR colorBrush)
{
	_animations[state]->render(x, y, false);
	this->state += 100;
	if (this->state > 400) this->state = 0;
}

void NotorBanger::SetState(int state)
{
	switch (state) {
	case NOTOR_BANGER_ANI_JUMP:
		speed.vy = -NOTOR_BANGER_SPEED;
		break;
	default:
		speed.vx = speed.vy = 0;
		break;
	}
}

void NotorBanger::loadResources()
{
	CTextures * textures = CTextures::getInstance();

	textures->add(NOTOR_BANGER_ID_TEXTURE, L"NotorBanger.png",0,0, D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();

	LPDIRECT3DTEXTURE9 textureNotorBanger = textures->getTexture(NOTOR_BANGER_ID_TEXTURE);

	LPANIMATION ani;

	// init
	sprites->addSprite(10001, NOTOR_BANGER_ID_TEXTURE, 7, 105, 40, 48); // 40 x 48
	sprites->addSprite(10002, NOTOR_BANGER_ID_TEXTURE, 52, 106, 40, 48);
	sprites->addSprite(10003, NOTOR_BANGER_ID_TEXTURE, 92, 105, 40, 48);
	sprites->addSprite(10004, NOTOR_BANGER_ID_TEXTURE, 136, 104, 40, 48);
	 
	ani = new CAnimation(500);
	ani->add(10001);
	ani->add(10002);
	ani->add(10003);
	ani->add(10004);
	animations->add(NOTOR_BANGER_STATE_INIT , ani);

	// shot
	sprites->addSprite(10011, NOTOR_BANGER_ID_TEXTURE, 176, 104, 40, 48); // 40 x 48

	ani = new CAnimation(100);
	ani->add(10011);
	animations->add(NOTOR_BANGER_STATE_SHOT, ani);

	// ready jump
	sprites->addSprite(10021, NOTOR_BANGER_ID_TEXTURE, 129, 52, 40, 48); // 40 x 48
	sprites->addSprite(10022, NOTOR_BANGER_ID_TEXTURE, 87, 52, 40, 48);
	sprites->addSprite(10023, NOTOR_BANGER_ID_TEXTURE, 45, 52, 40, 48);
	sprites->addSprite(10024, NOTOR_BANGER_ID_TEXTURE, 4, 52, 40, 48);

	ani = new CAnimation(100);
	ani->add(10021);
	ani->add(10022);
	ani->add(10023);
	ani->add(10024);
	animations->add(NOTOR_BANGER_STATE_READY_JUMP, ani);

	// jump
	sprites->addSprite(10031, NOTOR_BANGER_ID_TEXTURE, 146, 2, 48, 41);
	sprites->addSprite(10032, NOTOR_BANGER_ID_TEXTURE, 100, 6, 41, 32);
	sprites->addSprite(10033, NOTOR_BANGER_ID_TEXTURE, 48, 6, 41, 32);
	sprites->addSprite(10034, NOTOR_BANGER_ID_TEXTURE, 3, 6, 41, 32);

	ani = new CAnimation(250);
	ani->add(10031);
	ani->add(10032);
	ani->add(10033);
	ani->add(10034);
	animations->add(NOTOR_BANGER_STATE_JUMP, ani);

	// die
	sprites->addSprite(10041, NOTOR_BANGER_ID_TEXTURE, 8, 168, 18, 8);
	sprites->addSprite(10042, NOTOR_BANGER_ID_TEXTURE, 32, 165, 11, 12);
	sprites->addSprite(10043, NOTOR_BANGER_ID_TEXTURE, 47, 157, 22, 23);
	sprites->addSprite(10044, NOTOR_BANGER_ID_TEXTURE, 74, 157, 19, 20);

	ani = new CAnimation(100);
	ani->add(10041);
	ani->add(10042);
	ani->add(10043);
	ani->add(10044);
	animations->add(NOTOR_BANGER_STATE_DIE, ani);

	// add animation
	this->addAnimation(NOTOR_BANGER_STATE_INIT);
	this->addAnimation(NOTOR_BANGER_STATE_SHOT);
	this->addAnimation(NOTOR_BANGER_STATE_READY_JUMP);
	this->addAnimation(NOTOR_BANGER_STATE_JUMP);
	this->addAnimation(NOTOR_BANGER_STATE_DIE);
}


