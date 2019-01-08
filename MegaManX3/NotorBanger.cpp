#include "NotorBanger.h"


NotorBanger::NotorBanger(UINT id, float x, float y, bool nx) :DynamicObject(id, x, y, 0, 0)
{
	initDamage = 2.0f;
	this->nx = nx;
	this->repeat = 0;
	initHP = _hp = 3;
	setResetBound();
}

NotorBanger::~NotorBanger()
{
}

void NotorBanger::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{	
	this->dt = dt;
	updateWeapon(dt, staticObjects);

	if (!visible) return;

	if (_death) {
		calculateDie();
		return;
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
	collisionEffect->render(dt, false);
	renderWeapon(dt, colorBrush);

	if (!visible) return;

	if (_death) {
		renderDie(dt);
		collisionEffect->render(dt, false);
		timeHide.update();

		if (timeHide.isStop())
			visible = false;
	}
	else
	{
		renderNormal(dt, colorBrush);
	}
}


void NotorBanger::calculateDie()
{
	speed.vy += 0.00115f * dt;
	speed.vx += 0.000125 *dt;

	dx = speed.vx * dt;
	dy = speed.vy * dt;

	die[0].x += dx;
	die[1].x += dx * 1.25;
	die[2].x -= dx;
	die[3].x -= dx * 2;

	die[0].y += dy * 2;
	die[1].y += dy * 1.5;
	die[2].y += dy * 0.75;
	die[3].y += dy;
}

void NotorBanger::renderDie(DWORD dt, D3DCOLOR colorBrush)
{
	for (int i = 0; i < 4; ++i) {
		auto center = cameraGlobal->transform(die[i].x, die[i].y);
		_animations[NOTOR_BANGER_STATE_DIE + i ]->render(center.x, center.y, false, this->showColor ? WHITE(100) : WHITE(255));
	}
	if (++timeSwitchColor == 2)
		showColor = !showColor, timeSwitchColor = 0;
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
	}
	this->state = state;
	_animations[state]->reset();
}

void NotorBanger::loadResources()
{
	CTextures * textures = CTextures::getInstance();
	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();
	LPANIMATION ani;

	if (textures->getTexture(NOTOR_BANGER_ID_TEXTURE))
		goto LoadAni;

	textures->add(NOTOR_BANGER_ID_TEXTURE, L"Resource\\Textures\\enemies.png",0,0, D3DCOLOR_XRGB(255, 0, 255));
	// init
	sprites->addSprite(10001, NOTOR_BANGER_ID_TEXTURE, 7, 105, 40, 48); // 40 x 48
	sprites->addSprite(10002, NOTOR_BANGER_ID_TEXTURE, 52, 106, 40, 48);
	sprites->addSprite(10003, NOTOR_BANGER_ID_TEXTURE, 92, 105, 40, 48);
	sprites->addSprite(10004, NOTOR_BANGER_ID_TEXTURE, 136, 104, 40, 48);
	// shot small
	sprites->addSprite(10011, NOTOR_BANGER_ID_TEXTURE, 129, 52, 40, 48); // 40 x 48
	sprites->addSprite(10012, NOTOR_BANGER_ID_TEXTURE, 176, 104, 40, 48);
	// shot medium
	sprites->addSprite(10021, NOTOR_BANGER_ID_TEXTURE, 87, 52, 40, 48); // 40 x 48
	sprites->addSprite(10022, NOTOR_BANGER_ID_TEXTURE, 136, 104, 40, 48);
	// shot large
	sprites->addSprite(10031, NOTOR_BANGER_ID_TEXTURE, 45, 52, 40, 48); // 40 x 48
	sprites->addSprite(10032, NOTOR_BANGER_ID_TEXTURE, 92, 105, 40, 48);
	// ready jump small
	sprites->addSprite(10041, NOTOR_BANGER_ID_TEXTURE, 129, 52, 40, 48); // 40 x 48
	sprites->addSprite(10042, NOTOR_BANGER_ID_TEXTURE, 87, 52, 40, 48);
	sprites->addSprite(10043, NOTOR_BANGER_ID_TEXTURE, 45, 52, 40, 48);
	sprites->addSprite(10044, NOTOR_BANGER_ID_TEXTURE, 4, 52, 40, 48);
	// ready jump medium
	sprites->addSprite(10051, NOTOR_BANGER_ID_TEXTURE, 87, 52, 40, 48);
	sprites->addSprite(10052, NOTOR_BANGER_ID_TEXTURE, 45, 52, 40, 48);
	sprites->addSprite(10053, NOTOR_BANGER_ID_TEXTURE, 4, 52, 40, 48);
	// ready jump large
	sprites->addSprite(10061, NOTOR_BANGER_ID_TEXTURE, 45, 52, 40, 48);
	sprites->addSprite(10062, NOTOR_BANGER_ID_TEXTURE, 4, 52, 40, 48);
	// jump
	sprites->addSprite(10071, NOTOR_BANGER_ID_TEXTURE, 181, 0, 48, 48); // 48 x 48
	// touch floor
	sprites->addSprite(10081, NOTOR_BANGER_ID_TEXTURE, 128, 2, 48, 48);
	sprites->addSprite(10082, NOTOR_BANGER_ID_TEXTURE, 76, 2, 48, 48); // 48 x 48
	sprites->addSprite(10083, NOTOR_BANGER_ID_TEXTURE, 18, 2, 48, 48);
	// die
	sprites->addSprite(10091, NOTOR_BANGER_ID_TEXTURE, 8, 168, 18, 8);
	sprites->addSprite(10092, NOTOR_BANGER_ID_TEXTURE, 32, 165, 11, 12);
	sprites->addSprite(10093, NOTOR_BANGER_ID_TEXTURE, 47, 157, 22, 23);
	sprites->addSprite(10094, NOTOR_BANGER_ID_TEXTURE, 74, 157, 19, 20);

LoadAni :

	ani = new CAnimation(200);
	ani->add(10001);
	ani->add(10002);
	ani->add(10003);
	ani->add(10004);
	animations->add(NOTOR_BANGER_STATE_INIT , ani);



	ani = new CAnimation(600);
	ani->add(10011);
	ani->add(10012);
	animations->add(NOTOR_BANGER_STATE_SHOT_SMALL, ani);



	ani = new CAnimation(600);
	ani->add(10021);
	ani->add(10022);
	animations->add(NOTOR_BANGER_STATE_SHOT_MEDIUM, ani);



	ani = new CAnimation(600);
	ani->add(10031);
	ani->add(10032);
	animations->add(NOTOR_BANGER_STATE_SHOT_LARGE, ani);



	ani = new CAnimation(200);
	ani->add(10041);
	ani->add(10042);
	ani->add(10043);
	ani->add(10044);
	animations->add(NOTOR_BANGER_STATE_READY_JUMP_SMALL, ani);



	ani = new CAnimation(200);
	ani->add(10051);
	ani->add(10052);
	ani->add(10053);
	animations->add(NOTOR_BANGER_STATE_READY_JUMP_MEDIUM, ani);



	ani = new CAnimation(200);
	ani->add(10061);
	ani->add(10062);
	animations->add(NOTOR_BANGER_STATE_READY_JUMP_LARGE, ani);



	ani = new CAnimation(600);
	ani->add(10071);
	animations->add(NOTOR_BANGER_STATE_JUMP, ani);



	ani = new CAnimation(30);
	ani->add(10081);
	ani->add(10082);
	ani->add(10083);
	animations->add(NOTOR_BANGER_STATE_TOUCH_FLOOR, ani);



	for (int i = 0; i < 4; ++i)
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
	for (int i = 0; i < _weapons.size(); ++i)
	{
		auto bullet = dynamic_cast<NotorBangerBullet*>(_weapons[i]);
		if (bullet)
		{
			if (nx == true) bullet->setPosition(x + 10, y);
			else bullet->setPosition(x - 10, y);
		}

	}
}

void NotorBanger::setResetBound()
{
	resetBound.x = x;
	resetBound.y = y;
	resetBound.width = 40;
	resetBound.height = 48;
}

void NotorBanger::updateWeapon(DWORD dt, unordered_map<int, GameObject*>* staticObjects)
{
	for (auto bullet = _weapons.begin(); bullet != _weapons.end(); )
	{
		bullet[0]->update(dt, staticObjects);
		if (bullet[0]->getIsDelete())
		{
			int x = bullet[0]->x - 16;
			int y = bullet[0]->y - 20;
			collisionEffect->createEffect(x, y);
			delete bullet[0];
			bullet = _weapons.erase(bullet);
		}
		else ++bullet;
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

	_weapons.emplace_back(notorBangerBullet);

}

void NotorBanger::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (nx) {
		left = x + 0;
		top = y;
		right = x + 20;
		bottom = y + 48;
	}
	else //default 
	{
		left = x + 20;
		top = y;
		right = x + 40;
		bottom = y + 48;
	}
}

void NotorBanger::createExplosion(float x, float y)
{
	collisionEffect->createEffect(x, y);
}

void NotorBanger::setAnimationDie()
{
	die[0] = die[1] = die[2] = die[3] = { x, y };
	speed.vy = -0.0195f *dt;
	speed.vx = 0.0032f * dt;
	collisionEffect->createEffect(x, y);
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

void NotorBanger::collisionStatic(unordered_map<int, GameObject*>* staticObjects)
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

	}
	UINT size = coEvents.size();
	for (UINT i = 0; i < size; ++i) delete coEvents[i];
}

void NotorBanger::renderNormal(DWORD dt, D3DCOLOR colorBrush)
{
	if (_attacked)
	{
		timeAttacked.update();
		if (timeAttacked.isStop())
		{
			_attacked = false;
		}
		else colorBrush = LIGHTCYAN(128);
	}
	auto center = cameraGlobal->transform(x, y);
	if (nx != true)
		_animations[state]->render(center.x, center.y, false, colorBrush);
	else _animations[state]->renderFlipX(center.x, center.y, false, colorBrush);
	shotEffect->render(dt, true);
}

