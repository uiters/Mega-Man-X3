#include "NotorBanger.h"
#include "ConstGlobals.h"



NotorBanger::NotorBanger()
{
	this->x = 10;
	this->y = 300;
	this->nx = true;
	this->distance = 2;
	this->repeat = 0;
}

NotorBanger::NotorBanger(int id, float x, float y, bool nx, int distance)
{
	this->_id = id;
	this->x = x;
	this->y = y;
	this->nx = nx;
	this->distance = distance;
	this->repeat = 0;
}

NotorBanger::~NotorBanger()
{
}


void NotorBanger::update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects)
{	
	for (int i = 0; i < listBullet.size(); i++) {
		if (listBullet[i].isDelete) {
			listBullet.erase(listBullet.begin() + i);
		} else listBullet[i].update(dt);
	}

	GameObject::update(dt);

	speed.vy += NOTOR_BANGER_GRAVITY;
	x += dx;
	y += dy;

	if (speed.vx < 0 && x < 0) {
		speed.vx = -speed.vx;
		nx = true;
	}

	if (speed.vx > 0 && x > 300) {
		speed.vx = -speed.vx;
		nx = false;
	}

	if (speed.vy < 0 && y < 260) {
		y = 260;
	}

	if (speed.vy > 0 && y > 300) {
		y = 300;
	}

	if (_animations[state]->isLastFrame()) {
		switch (state)
		{
		case 0: 
			switch (distance)
			{
			case 0:
				state += 100;
				break;
			case 1:
				state += 200;
				break;
			case 2:
				state += 300;
				break;
			default:
				break;
			}
			break;
		case 100:
			if (repeat == 2)
				state += 300;
			createBullet();
			repeat++;
			if (repeat > 2) 
				repeat = 0;
			break;
		case 200:
			if (repeat == 2)
				state += 300;
			createBullet();
			repeat++;
			if (repeat > 2) 
				repeat = 0;
			break;
		case 300:
			if (repeat == 2)
				state += 300;
			createBullet();
			repeat++;
			if (repeat > 2) 
				repeat = 0;
			break;
		case 400:
			state += 300;
			break;
		case 500:
			state += 200;
			break;
		case 800:
			// clear bullet
			state += 100;
			break;
		default:
			state += 100;
			break;
		}

		if (state > 800) state = 0;
		setState(state);
	}
}

void NotorBanger::render(DWORD dt, D3DCOLOR colorBrush)
{	
	for (int i = 0; i < listBullet.size(); i++)
	{
		listBullet[i].render(dt);
	}

	if (nx != true) _animations[state]->render(x, y, false);
	else _animations[state]->renderFlipX(x, y);
}

void NotorBanger::setState(int state)
{
	switch (state) {
	case NOTOR_BANGER_STATE_JUMP:
		speed.vy = -NOTOR_BANGER_SPEED_Y;
		speed.vx = nx == true ? NOTOR_BANGER_SPEED_X : -NOTOR_BANGER_SPEED_X;
		break;
	case NOTOR_BANGER_STATE_TOUCH_FLOOR:
		speed.vy = NOTOR_BANGER_SPEED_Y;
		speed.vx = nx == true ? NOTOR_BANGER_SPEED_X : -NOTOR_BANGER_SPEED_X;
		break;
	default:
		speed.vx = 0;
		speed.vy = 0;
		break;
	}
	this->state = state;
	_animations[state]->reset();
}

void NotorBanger::loadResources()
{

	CTextures * textures = CTextures::getInstance();

	textures->add(NOTOR_BANGER_ID_TEXTURE, L"enemies.png",0,0, D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();

	//LPDIRECT3DTEXTURE9 textureNotorBanger = textures->getTexture(NOTOR_BANGER_ID_TEXTURE);

	LPANIMATION ani;

	// init
	sprites->addSprite(10001, NOTOR_BANGER_ID_TEXTURE, 7, 105, 40, 48); // 40 x 48
	sprites->addSprite(10002, NOTOR_BANGER_ID_TEXTURE, 52, 106, 40, 48);
	sprites->addSprite(10003, NOTOR_BANGER_ID_TEXTURE, 92, 105, 40, 48);
	sprites->addSprite(10004, NOTOR_BANGER_ID_TEXTURE, 136, 104, 40, 48);
	 
	ani = new CAnimation(200);
	ani->add(10001);
	ani->add(10002);
	ani->add(10003);
	ani->add(10004);
	animations->add(NOTOR_BANGER_STATE_INIT , ani);

	// shot small
	sprites->addSprite(10011, NOTOR_BANGER_ID_TEXTURE, 129, 52, 40, 48); // 40 x 48
	sprites->addSprite(10012, NOTOR_BANGER_ID_TEXTURE, 176, 104, 40, 48);

	ani = new CAnimation(500);
	ani->add(10011);
	ani->add(10012);
	animations->add(NOTOR_BANGER_STATE_SHOT_SMALL, ani);

	// shot medium
	sprites->addSprite(10021, NOTOR_BANGER_ID_TEXTURE, 87, 52, 40, 48); // 40 x 48
	sprites->addSprite(10022, NOTOR_BANGER_ID_TEXTURE, 136, 104, 40, 48);

	ani = new CAnimation(500);
	ani->add(10021);
	ani->add(10022);
	animations->add(NOTOR_BANGER_STATE_SHOT_MEDIUM, ani);

	// shot large
	sprites->addSprite(10031, NOTOR_BANGER_ID_TEXTURE, 45, 52, 40, 48); // 40 x 48
	sprites->addSprite(10032, NOTOR_BANGER_ID_TEXTURE, 92, 105, 40, 48);

	ani = new CAnimation(500);
	ani->add(10031);
	ani->add(10032);
	animations->add(NOTOR_BANGER_STATE_SHOT_LARGE, ani);

	// ready jump small
	sprites->addSprite(10041, NOTOR_BANGER_ID_TEXTURE, 129, 52, 40, 48); // 40 x 48
	sprites->addSprite(10042, NOTOR_BANGER_ID_TEXTURE, 87, 52, 40, 48);
	sprites->addSprite(10043, NOTOR_BANGER_ID_TEXTURE, 45, 52, 40, 48);
	sprites->addSprite(10044, NOTOR_BANGER_ID_TEXTURE, 4, 52, 40, 48);

	ani = new CAnimation(200);
	ani->add(10041);
	ani->add(10042);
	ani->add(10043);
	ani->add(10044);
	animations->add(NOTOR_BANGER_STATE_READY_JUMP_SMALL, ani);

	// ready jump medium
	sprites->addSprite(10051, NOTOR_BANGER_ID_TEXTURE, 87, 52, 40, 48);
	sprites->addSprite(10052, NOTOR_BANGER_ID_TEXTURE, 45, 52, 40, 48);
	sprites->addSprite(10053, NOTOR_BANGER_ID_TEXTURE, 4, 52, 40, 48);

	ani = new CAnimation(200);
	ani->add(10051);
	ani->add(10052);
	ani->add(10053);
	animations->add(NOTOR_BANGER_STATE_READY_JUMP_MEDIUM, ani);

	// ready jump large
	sprites->addSprite(10061, NOTOR_BANGER_ID_TEXTURE, 45, 52, 40, 48);
	sprites->addSprite(10062, NOTOR_BANGER_ID_TEXTURE, 4, 52, 40, 48);

	ani = new CAnimation(200);
	ani->add(10061);
	ani->add(10062);
	animations->add(NOTOR_BANGER_STATE_READY_JUMP_LARGE, ani);

	// jump
	sprites->addSprite(10071, NOTOR_BANGER_ID_TEXTURE, 181, 0, 48, 48); // 48 x 48

	ani = new CAnimation(500);
	ani->add(10071);
	animations->add(NOTOR_BANGER_STATE_JUMP, ani);

	// touch floor
	sprites->addSprite(10081, NOTOR_BANGER_ID_TEXTURE, 128, 2, 48, 48);
	sprites->addSprite(10082, NOTOR_BANGER_ID_TEXTURE, 76, 2, 48, 48); // 48 x 48
	sprites->addSprite(10083, NOTOR_BANGER_ID_TEXTURE, 18, 2, 48, 48);

	ani = new CAnimation(100);
	ani->add(10081);
	ani->add(10082);
	ani->add(10083);
	animations->add(NOTOR_BANGER_STATE_TOUCH_FLOOR, ani);

	// die
	sprites->addSprite(10091, NOTOR_BANGER_ID_TEXTURE, 8, 168, 18, 8);
	sprites->addSprite(10092, NOTOR_BANGER_ID_TEXTURE, 32, 165, 11, 12);
	sprites->addSprite(10093, NOTOR_BANGER_ID_TEXTURE, 47, 157, 22, 23);
	sprites->addSprite(10094, NOTOR_BANGER_ID_TEXTURE, 74, 157, 19, 20);

	ani = new CAnimation(200);
	ani->add(10091);
	ani->add(10092);
	ani->add(10093);
	ani->add(10094);
	animations->add(NOTOR_BANGER_STATE_DIE, ani);

	// add animations
	this->addAnimation(NOTOR_BANGER_STATE_INIT);
	this->addAnimation(NOTOR_BANGER_STATE_SHOT_SMALL);
	this->addAnimation(NOTOR_BANGER_STATE_SHOT_MEDIUM);
	this->addAnimation(NOTOR_BANGER_STATE_SHOT_LARGE);
	this->addAnimation(NOTOR_BANGER_STATE_READY_JUMP_SMALL);
	this->addAnimation(NOTOR_BANGER_STATE_READY_JUMP_MEDIUM);
	this->addAnimation(NOTOR_BANGER_STATE_READY_JUMP_LARGE);
	this->addAnimation(NOTOR_BANGER_STATE_JUMP);
	this->addAnimation(NOTOR_BANGER_STATE_TOUCH_FLOOR);
	this->addAnimation(NOTOR_BANGER_STATE_DIE);
}

void NotorBanger::setPositionForListBullet()
{
	for (int i = 0; i < listBullet.size(); i++)
	{
		if (nx == true) listBullet[i].setPosition(x + 10, y);
		else listBullet[i].setPosition(x - 10, y);
	}
}

void NotorBanger::createBullet()
{	
	int x, y;
	switch (distance)
	{
	case 0:
		x = nx == true ? this->x + 10 : this->x + 20;
		break;
	case 1:
		x = nx == true ? this->x + 20 : this->x + 8;
		break;
	case 2:
		x = nx == true ? this->x + 30 : this->x - 2;
		break;
	default:
		break;
	}
	NotorBangerBullet* notorBangerBullet = new NotorBangerBullet(
		x, 
		this->y - 2, 
		true, 
		false,
		distance
	);
	notorBangerBullet->nx = this->nx;
	notorBangerBullet->loadResources();
	notorBangerBullet->setState(NOTOR_BANGER_BULLET_STATE_DEFAULT);
	listBullet.push_back(*notorBangerBullet);
}

void NotorBanger::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

NotorBanger * NotorBanger::clone(int id, int x, int y)
{
	return nullptr;
}

