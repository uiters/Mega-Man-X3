#include "BlastHornet.h"

HornetPoint* BlastHornet::getHoretPoint() { return hornetPoint; }

BlastHornet::BlastHornet()
{
	loadResources();
	hornetPoint = new HornetPoint();
	effect = HornetExplosion::getInstance();
	x = 7863;

	y = 1485;

	speed.vy = 0.55f;
	
	mech = &BlastHornet::start;
	mechBerk = &BlastHornet::berserkDropBeePrepare;


	toLeft = true;
	
	initHP = 32.0f; //hp
	width = 44;
	height = 57;
}


BlastHornet::~BlastHornet()
{

}

void BlastHornet::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	if (visible)
	{
		GameObject::update(dt);
		if (_death)
		{
			timeHide.update();
			if (timeHide.isStop())
			{
				visible = false;
				return;
			}
			if(!isCollisionStatic) 
				isCollisionStatic = collisionStatic(),
				speed.vy += 0.01f * dt;
			else
			{
				timeDelayExplosion.update();
				if (timeDelayExplosion.isStop())
				{
					effect->createEffect(x + 32 + rand() % 50 - 10, y + 10 + rand() % 40 - 10);
					timeDelayExplosion.start();
					soundsGlobal->play(sound_explosion);
				}
			}
			
		}
		else
		{
			this->currentStatic = staticObjects;
			(this->*mech)();
			updateWeapon(dt, staticObjects);
		}
	}
}

void BlastHornet::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (visible)
	{
		if (_death)
		{
			if (color > 10)
			{
				color -= 1;
			}
			auto pos = cameraGlobal->transform(x, y);
			if (toLeft) _animations[state]->render(pos.x, pos.y, false, WHITE(color));
				else _animations[state]->renderFlipX(pos.x, pos.y, false, WHITE(color));
			effect->render(dt, true);
			return;
		}
		else
		{
			auto pos = cameraGlobal->transform(x, y);

			if (toLeft)
				_animations[Hornet_Wing]->render(pos.x + 27, pos.y - 2, true),
				_animations[state]->render(pos.x, pos.y);
			else
				_animations[Hornet_Wing]->render(pos.x + 17.f, pos.y - 1, true),
				_animations[state]->renderFlipX(pos.x, pos.y);

			renderWeapon(dt);
		}
	}
}

void BlastHornet::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void BlastHornet::reset()
{
	x = 7863;
	y = 1485;

	speed.vy = 0.55f;
	this->dx = 0;
	this->dy = 0;
	mech = &BlastHornet::start;
	mechBerk = &BlastHornet::berserkDropBeePrepare;

	toLeft = true;
	_hp = 0;
	initHP = 64.0f; //hp
	width = 44;
	height = 57;
	this->setState(Hornet_Show);

	delete hornetPoint;
	hornetPoint = new HornetPoint();
	auto size = _weapons.size();
	for (int i = 0; i < size; ++i)
	{
		delete _weapons.at(i);
	}
	_weapons.clear();
}

void BlastHornet::flyArround()
{
	setDirection();

	if (x > 7730 && x < 7835)
	{
		if (speed.vy < 0)
			speed.vy = 0.0150f,
			++round;;
		checkY = 1;		
	}
	else
	{
		if (x < 7700)
		{
			if(speed.vx < 0) speed.vx = 0.f;
			checkX = 1;
		}else
			if (x > 7865)
			{
				if (speed.vx > 0) speed.vx = 0.f;
				checkX = -1;
			}
		//else checkX = -1;

		if (speed.vy > 0)
			speed.vy = -0.01750f;//speed.vy = -1 * speed.vy;speed.vy
			//++round; 

		checkY = -1;
	}
	speed.vx += checkX * 0.00010f * dt;
	speed.vy += checkY * 0.00013f * dt;

	collisionStatic();
}

void BlastHornet::setState(UINT state)
{
	this->state = state;
	_animations[state]->reset();
}

bool BlastHornet::collisionStatic()
{
	vector<CollisionEvent*> coEvents;
	vector<CollisionEvent*> coEventsResult;
	bool check = false;
	collision->findCollisions(dt, this, *currentStatic, coEvents);
	UINT size = coEvents.size();

	if (size == 0)
	{
		x += dx;
		y += dy;
		
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		collision->filterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		check = true;
	}
	for (UINT i = 0; i < size; ++i) delete coEvents[i];
	return check;
}


void BlastHornet::fly()
{
	float distanceX = 0;
	float distanceY = 1562 - y;
	if (isFirst)
	{
		isFirst = false;
		toLeft = true;
		distanceX = 7863 - x;
	}
	else
	{
		toLeft = rand() % 3;
		if (toLeft)
		{
			distanceX = 7863 - x;
		}
		else
			distanceX = 7707 - x;
		toLeft = !toLeft;
	}
	lockDirection = true;

	speed.vy = distanceY / 1000.f; //calculate speed
	speed.vx = distanceX / 1000.f;
	

}

//start
void BlastHornet::start()
{
	if (_animations[state]->isLastFrame())
	{
		mech = &BlastHornet::addHP;
		speed.vy = 0;
		state = Hornet_Stand;
		width = 44;
		height = 57;
	}
	else
	{
		if (stop) return;

		if (isDone)
		{
			speed.vy += 0.00125f * dt;

			this->y += dy;

			if (speed.vy > 0.f) stop = true;
		}
		else
		{
			speed.vy -= 0.00091f * dt;
			this->y += dy;
			if (speed.vy <= 0) 
				isDone = true,
				speed.vy = -0.35f;
		}
	}
}

void BlastHornet::addHP()
{
	++_hp;
	if (_hp == initHP - 00.f) // test
	{
		mech = &BlastHornet::mech1;
		fly();
		initDamage = 3.0f;
	}
}

//prick
void BlastHornet::mech1()
{
	if (y + dy <= 1562)
	{
		y = 1562;
		mech = &BlastHornet::prickPrepare;
		state = Hornet_Prepare_Prick;
		_animations[state]->reset();
		lockDirection = false;
		width = 44;
		height = 57;
	}
	else
		y += dy, x += dx;
}

void BlastHornet::prickPrepare()
{
	if (_animations[Hornet_Prepare_Prick]->isLastFrame())
	{
		state = Hornet_Prick;
		mech = &BlastHornet::prick;
		_animations[state]->reset();
		aimPrick();
		setDirection();
	}
}

void BlastHornet::aimPrick()
{
	float distanceX = mainGlobal->x - x;
	float distanceY = mainGlobal->y - y;

	speed.vy = distanceY / 350.f; //calculate speed
	speed.vx = distanceX / 350.f;
	initDamage = 8.0f;
}

void BlastHornet::prick()
{
	vector<CollisionEvent*> coEvents;
	vector<CollisionEvent*> coEventsResult;

	collision->findCollisions(dt, this, *currentStatic, coEvents);
	UINT size = coEvents.size();

	if (size == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		collision->filterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 1.f;
		y += min_ty * dy + ny * 0.4f;

		if (ny != 0 || nx != 0)
		{
			speed.vx = 0.0f;
			speed.vy = 0.0f;
			state = Hornet_Prick_End;
			mech = &BlastHornet::prickEnd;
			_animations[state]->reset();
		}
	}
	for (UINT i = 0; i < size; ++i) delete coEvents[i];
}

void BlastHornet::prickEnd()
{
	if (_animations[Hornet_Prick_End]->isLastFrame())
	{
		state = Hornet_Stand;
		mech = &BlastHornet::mech2;
		fly();
		initDamage = 3.0f;
	}
}

//drop bee
void BlastHornet::mech2()
{
	if (y + dy <= 1562)
	{
		if (_hp / initHP < 0.5f)
		{
			mech = &BlastHornet::berserk;
			timeDropBee.start();
			timeDropAim.start();
			width = 44;
			height = 57;
		}
		else
		{
			y = 1562;
			mech = &BlastHornet::dropBeePrepare;
			setState(Hornet_Drop_Bee_1);
			lockDirection = false;
			width = 44;
			height = 57;
			setDirection();
		}
	}
	else
		y += dy, x += dx;
}

void BlastHornet::dropBeePrepare()
{
	if (_animations[state]->isLastFrame())
	{
		setState(Hornet_Drop_Bee_1_1);
		mech = &BlastHornet::dropBee;
		createBee();
	}
}

void BlastHornet::createBee()
{
	float distanceX = mainGlobal->x - x;
	float distanceY = mainGlobal->y - y;
	float vx = 0.0f;
	float vy = 0.0f;

	for (int i = 0; i < 6; ++i)
	{
		vy = (distanceY) / 1000.f; //calculate speed
		vx = (distanceX - i * 40.f) / 1000.f;
		if(toLeft)
			_weapons.emplace_back(new Bee(x, y, vx, vy, toLeft, false));
		else
			_weapons.emplace_back(new Bee(x + width, y, vx, vy, toLeft, false));

	}
}

void BlastHornet::dropBee()
{
	if (_animations[state]->isLastFrame())
	{
		setState(Hornet_Drop_Bee_1_End);
		mech = &BlastHornet::dropBeeEnd;
	}
}

void BlastHornet::dropBeeEnd()
{
	if (_animations[state]->isLastFrame())
	{
		state = Hornet_Stand;
		mech = &BlastHornet::mech3;
		maxRound = rand() % 3 + 1; // [1, 3] 1 = haft circle
	}
}

//fly around
void BlastHornet::mech3()
{
	flyArround();
	
	if (round > maxRound)
	{
		if (_hp / initHP < 0.5f)
		{
			mech = &BlastHornet::berserk;
			timeDropBee.start();
			timeDropAim.start();
			width = 44;
			height = 57;
		}
		else
		{
			mech = &BlastHornet::mech1;
			round = 0;
		}
	}
}

//fly around & drop bee
void BlastHornet::berserk()
{
	timeDropAim.update();
	flyArround();
	(this->*mechBerk)();

	if (timeDropAim.isRunning())
	{
		hornetPoint->update(dt);
	}
	else
	{
		timeDropAim.start();
		hornetPoint->setLocation(this->x, this->y);
		hornetPoint->show();
	}
}

void BlastHornet::berserkDropBeePrepare()
{
	timeDropBee.update();
	if (timeDropBee.isStop())
	{
		setState(Hornet_Drop_Bee_2_Prepare);
		mechBerk = &BlastHornet::berserkDropBee;
	}
}

void BlastHornet::berserkDropBee()
{
	
	if (_animations[state]->isLastFrame())
	{
		setState(Hornet_Drop_Bee_2_End);
		mechBerk = &BlastHornet::berserkDropBeeEnd;
		bees = 0;
	}
	else
	{
		delay.update();
		if (bees < maxBee && delay.isStop())
		{
			if(toLeft)
				_weapons.emplace_back(new Bee(x + 9, y + 47, 0, 0, toLeft, true));
			else
				_weapons.emplace_back(new Bee(x + 27, y + 47, 0, 0, toLeft, true));

			delay.start();
			bees += 1;
		}

	}
}

void BlastHornet::berserkDropBeeEnd()
{
	if (_animations[state]->isLastFrame())
	{
		state = Hornet_Stand;
		mechBerk = &BlastHornet::berserkDropBeePrepare;
		timeDropBee.setTimeUp(rand() % 2000 + 3500);// [2500, 5500]
		timeDropBee.start();
		
	}
}

void BlastHornet::receiveDamage(float damage)
{
	if (_hp > 0.0f)
	{
		_hp -= damage;
	}
	if (_hp <= 0.0f)
	{
		timeHide = (8000);
		timeHide.start();

		timeDelayExplosion = (200);
		timeDelayExplosion.start();
		
		_death = true;
		state = Hornet_Die;
		height = 48;
		width = 32;
		x -= 32;
		speed.vx = 0;
		speed.vy = 0.15f;
	}
}


//update weapons
void BlastHornet::updateWeapon(DWORD dt, unordered_map<int, GameObject*>* staticObjects)
{
	for (auto bullet = _weapons.begin(); bullet != _weapons.end();)
	{
		bullet[0]->update(dt, staticObjects);

		if (bullet[0]->getIsDelete())
		{
			delete bullet[0];
			bullet = _weapons.erase(bullet);
		}
		else ++bullet;
	}
}

void BlastHornet::setDirection()
{
	if (x + width / 2 > mainGlobal->x)
		toLeft = true;
	else
		toLeft = false;
}

void BlastHornet::loadResources()
{

#pragma region Load Sprite

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
	spritesGlobal->addSprite(Hornet_Prepare_Prick + 10, TBlastHornet, 315 - 1, 94, 43 + 1, 57);
	spritesGlobal->addSprite(Hornet_Prepare_Prick + 11, TBlastHornet, 364, 94, 44, 58);

	//die
	spritesGlobal->addSprite(Hornet_Die, TBlastHornet, 414, 102, 96, 48);



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
	spritesGlobal->addSprite(Hornet_Bee_Die_1, TBlastHornet, 17 - 2, 198, 19 + 2, 22);
	spritesGlobal->addSprite(Hornet_Bee_Die_1 + 1, TBlastHornet, 41 - 2, 198, 19 + 2, 22);

	//bee die_2
	spritesGlobal->addSprite(Hornet_Bee_Die_2, TBlastHornet, 64, 198, 22, 22);




	//aim
	spritesGlobal->addSprite(Hornet_Aim, TBlastHornet, 96, 186, 15, 15);
	spritesGlobal->addSprite(Hornet_Aim + 1, TBlastHornet, 113, 186, 15, 15);

	//aiming
	spritesGlobal->addSprite(Hornet_Aimming, TBlastHornet, 131, 182, 23, 23);
	spritesGlobal->addSprite(Hornet_Aimming + 1, TBlastHornet, 158, 182, 23, 23);

#pragma endregion

#pragma region Prick


	//stand
	CAnimation* ani = new CAnimation(100);
	ani->add(Hornet_Stand, 200);
	_animations[Hornet_Stand] = ani;

	//prick
	ani = new AnimationOneTime(80);
	ani->add(Hornet_Stand, 200);
	for (int i = 0; i < 12; ++i)
	{
		ani->add(Hornet_Prepare_Prick + i);
	}
	ani->add(Hornet_Prepare_Prick + 5, 500);
	_animations[Hornet_Prepare_Prick] = ani;

	//prick 
	ani = new CAnimation(100);
	ani->add(Hornet_Prepare_Prick + 5);

	_animations[Hornet_Prick] = ani;

	//prick end
	ani = new AnimationOneTime(80);
	for (int i = 5; i > -1; --i)
	{
		ani->add(Hornet_Prepare_Prick + i);
	}
	ani->add(Hornet_Stand, 500);
	_animations[Hornet_Prick_End] = ani;

#pragma endregion

#pragma region Drop bee
	//drop bee 1
	ani = new AnimationOneTime(100);
	ani->add(Hornet_Stand, 300);
	for (int i = 0; i < 2; ++i)
	{
		ani->add(Hornet_Drop_Bee_1 + i);
	}
	ani->add(Hornet_Drop_Bee_1 + 2, 500);
	_animations[Hornet_Drop_Bee_1] = ani;

	//drop bee 1_1
	ani = new AnimationOneTime(300);
	ani->add(Hornet_Drop_Bee_1 + 3);
	_animations[Hornet_Drop_Bee_1_1] = ani;

	//drop bee_1 end
	ani = new AnimationOneTime(100);
	ani->add(Hornet_Drop_Bee_1 + 4);
	ani->add(Hornet_Drop_Bee_1 + 1);
	ani->add(Hornet_Drop_Bee_1);
	ani->add(Hornet_Stand, 500);

	_animations[Hornet_Drop_Bee_1_End] = ani;

	//drop bee 2 prepare
	ani = new AnimationOneTime(100);
	for (int i = 0; i < 3; ++i)
	{
		ani->add(Hornet_Prepare_Prick + i);
	}
	ani->add(Hornet_Prepare_Prick + 3, 500);
	_animations[Hornet_Drop_Bee_2_Prepare] = ani;

	//drop bee 2 end
	ani = new AnimationOneTime(100);
	for (int i = 2; i > -1; --i)
	{
		ani->add(Hornet_Prepare_Prick + i);
	}
	//ani->add(Hornet_Stand, 2000);
	_animations[Hornet_Drop_Bee_2_End] = ani;

#pragma endregion

#pragma region Wing
	//wing
	ani = new CAnimation(40);
	ani->add(Hornet_Wing);
	ani->add(Hornet_Wing + 1);
	ani->add(Hornet_Wing + 2);
	_animations[Hornet_Wing] = ani;

	ani = new CAnimation(100);
	ani->add(Hornet_Wing);
#pragma endregion

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

#pragma endregion

#pragma region Aim
	ani = new CAnimation(100);
	ani->add(Hornet_Aim);
	ani->add(Hornet_Aim + 1);
	animationsGlobal->add(Hornet_Aim, ani);
	//_animations[Hornet_Aim] = ani;

	ani = new CAnimation(100);
	ani->add(Hornet_Aimming);
	ani->add(Hornet_Aimming + 1);
	animationsGlobal->add(Hornet_Aimming, ani);
	//_animations[Hornet_Aimming] = ani;
#pragma endregion

#pragma region Die
	//hornet die
	ani = new CAnimation(5000);
	ani->add(Hornet_Die);
	_animations[Hornet_Die] = ani;

#pragma endregion

#pragma region Show
	ani = new AnimationOneTime(100);
	ani->add(Hornet_Stand, 1000);
	ani->add(Hornet_Drop_Bee_1 + 0);
	ani->add(Hornet_Drop_Bee_1 + 1);
	ani->add(Hornet_Drop_Bee_1 + 2, 500);
	ani->add(Hornet_Drop_Bee_1 + 1);
	ani->add(Hornet_Drop_Bee_1);

	for (int i = 0; i < 6; ++i)
	{
		ani->add(Hornet_Prepare_Prick + i, 90);
	}
	for (int i = 5; i > -1; --i)
	{
		ani->add(Hornet_Prepare_Prick + i);
	}
	_animations[Hornet_Show] = ani;
#pragma endregion

	state = Hornet_Show;
}
