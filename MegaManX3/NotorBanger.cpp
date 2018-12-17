#include "NotorBanger.h"


NotorBanger::NotorBanger()
{
	this->x = 10;
	this->y = 300;
	this->initX = this->x;
	this->initY = this->y;
	this->nx = true;
	this->repeat = 0;
}

NotorBanger::NotorBanger(int id, float x, float y, bool nx)
{
	this->_id = id;
	this->x = x;
	this->y = y;
	this->initX = x;
	this->initY = y;
	this->nx = nx;
	this->repeat = 0;

	die[0] = die[1] = die[2] = die[3] = { x, y };
	speed.vy = -0.0195f *dt;
	speed.vx = 0.0032f * dt;
	_death = false;
}

NotorBanger::~NotorBanger()
{
}

void NotorBanger::update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects)
{	
	this->dt = dt;
	if (_death) {
		calculateDie();
		return;
	}

	for (int i = 0; i < listBullet.size(); i++) {
		if (listBullet[i].isDelete) {
			int x = listBullet[i].x - 16;
			int y = listBullet[i].y - 20;
			collisionEffect->createEffect(x, y);
			listBullet.erase(listBullet.begin() + i);
		} else listBullet[i].update(dt, staticObjects);
	}

	GameObject::update(dt);

	speed.vy += NOTOR_BANGER_GRAVITY * dt;

	collisionStatic(staticObjects);

	if (_animations[state]->isLastFrame()) {
		switch (state)
		{
		case 0: 
			switch (this->getDistance())
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
			if (mainGlobal != NULL)
				if (abs(this->y - mainGlobal->y) <= 30)
					if (mainGlobal->x > this->x)
						this->nx = !mainGlobal->toLeft;
					else this->nx = mainGlobal->toLeft;
			break;
		case 100:
		case 200:
		case 300:
			createBullet();
			if (repeat == 2)
				state += 300;

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
			state += 100;
			break;
		default:
			state += 100;
		}

		if (state > 800) state = 0; //800
		setState(state);
	}
}

void NotorBanger::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (_death) {
		renderDie(dt);
		collisionEffect->render(dt, false);
		return;
	}	

	auto center = cameraGlobal->transform(x, y);
	if (nx != true)
		_animations[state]->render(center.x, center.y);
	else _animations[state]->renderFlipX(center.x, center.y);

	for (int i = 0; i < listBullet.size(); i++)
	{
		listBullet[i].render(dt);
	}

	shotEffect->render(dt, true);
	collisionEffect->render(dt, false);
		
}

void NotorBanger::calculateDie()
{
	speed.vy += 0.00115f * dt;
	speed.vx += 0.000125 *dt;

	dx = speed.vx * dt;
	dy = speed.vy * dt;

	die[0].x += dx;
	die[1].x += dx * 2;
	die[2].x -= dx;
	die[3].x -= dx * 2;

	die[0].y += dy;
	die[1].y += dy;
	die[2].y += dy;
	die[3].y += dy;

	//debugOut(L"%f %f %f %f %f %f ", dieX[0].x, dieX[0].y);
}

void NotorBanger::renderDie(DWORD dt, D3DCOLOR colorBrush)
{

	for (int i = 0; i < 4; i++) {
		auto center = cameraGlobal->transform(die[i].x, die[i].y);
		_animations[NOTOR_BANGER_STATE_DIE + i ]->render(center.x, center.y);
	}
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

	if (textures->getTexture(NOTOR_BANGER_ID_TEXTURE) == NULL)
	textures->add(NOTOR_BANGER_ID_TEXTURE, L"Resource\\Textures\\enemies.png",0,0, D3DCOLOR_XRGB(255, 0, 255));

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

	ani = new CAnimation(600);
	ani->add(10011);
	ani->add(10012);
	animations->add(NOTOR_BANGER_STATE_SHOT_SMALL, ani);

	// shot medium
	sprites->addSprite(10021, NOTOR_BANGER_ID_TEXTURE, 87, 52, 40, 48); // 40 x 48
	sprites->addSprite(10022, NOTOR_BANGER_ID_TEXTURE, 136, 104, 40, 48);

	ani = new CAnimation(600);
	ani->add(10021);
	ani->add(10022);
	animations->add(NOTOR_BANGER_STATE_SHOT_MEDIUM, ani);

	// shot large
	sprites->addSprite(10031, NOTOR_BANGER_ID_TEXTURE, 45, 52, 40, 48); // 40 x 48
	sprites->addSprite(10032, NOTOR_BANGER_ID_TEXTURE, 92, 105, 40, 48);

	ani = new CAnimation(600);
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

	ani = new CAnimation(600);
	ani->add(10071);
	animations->add(NOTOR_BANGER_STATE_JUMP, ani);

	// touch floor
	sprites->addSprite(10081, NOTOR_BANGER_ID_TEXTURE, 128, 2, 48, 48);
	sprites->addSprite(10082, NOTOR_BANGER_ID_TEXTURE, 76, 2, 48, 48); // 48 x 48
	sprites->addSprite(10083, NOTOR_BANGER_ID_TEXTURE, 18, 2, 48, 48);

	ani = new CAnimation(30);
	ani->add(10081);
	ani->add(10082);
	ani->add(10083);
	animations->add(NOTOR_BANGER_STATE_TOUCH_FLOOR, ani);

	// die
	sprites->addSprite(10091, NOTOR_BANGER_ID_TEXTURE, 8, 168, 18, 8);
	sprites->addSprite(10092, NOTOR_BANGER_ID_TEXTURE, 32, 165, 11, 12);
	sprites->addSprite(10093, NOTOR_BANGER_ID_TEXTURE, 47, 157, 22, 23);
	sprites->addSprite(10094, NOTOR_BANGER_ID_TEXTURE, 74, 157, 19, 20);

	for (int i = 0; i < 4; i++)
	{
		ani = new CAnimation(100);
		ani->add(10091 + i);
		animations->add(NOTOR_BANGER_STATE_DIE + i, ani);
		this->addAnimation(NOTOR_BANGER_STATE_DIE + i);
	}

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
	switch (this->getDistance())
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

	shotEffect->createEffect(x + 5, this->y);

	NotorBangerBullet* notorBangerBullet = new NotorBangerBullet(
		x,
		this->y - 2,
		this->nx,
		false,
		this->getDistance()
	);
	notorBangerBullet->loadResources();
	notorBangerBullet->setState(NOTOR_BANGER_BULLET_STATE_DEFAULT);
	listBullet.push_back(*notorBangerBullet);

}

void NotorBanger::resetPosition()
{
	this->x = this->initX;
	this->y = this->initY;
}

void NotorBanger::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 40;
	bottom = y + 48;
}

NotorBanger * NotorBanger::clone(int id, int x, int y)
{
	return nullptr;
}

int NotorBanger::getDistance()
{
	float mainX = mainGlobal->x;
	float mainY = mainGlobal->y;

	Distance distance;
	distance.width = abs(mainX - this->x);
	distance.height = abs(mainY - this->y);

	if (distance.height > 30) return 0;
	if (distance.height <= 30) {
		if (distance.width < 50) return 0;
		if (distance.width >= 50 && distance.width < 100) return 1;
		return 2;
	}
}

void NotorBanger::collisionStatic(unordered_map<int, CTreeObject*>* staticObjects)
{
	vector<CollisionEvent*> coEvents;
	vector<CollisionEvent*> coEventsResult;

	collision->findCollisions(dt, this, *staticObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		collision->filterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 1.f;
		y += min_ty * dy + ny * 1.f;
		//if (speed.vx > 0 && nx > 0)//left
		//{
		//	speed.vx = -speed.vx;
		//	this->nx = true;
		//}
		//else if (speed.vx < 0 && nx < 0)//right
		//{
		//	speed.vx = -speed.vx;
		//	this->nx = false;
		//}

	}
	UINT size = coEvents.size();
	for (UINT i = 0; i < size; ++i) delete coEvents[i];
}

