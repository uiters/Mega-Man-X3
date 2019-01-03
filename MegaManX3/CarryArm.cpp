#include "CarryArm.h"


CarryArm::CarryArm(float x, float y, bool isNext)
{
	srand(time(NULL));
	int number = rand() % 10 + 1;

	this->isNext = isNext;
	this->isLeft = number >= 5 ? true : false;

	this->x = isLeft ? (!isNext ? x : x + 59) : (!isNext ? x + 200 : x + 200 + 59);
	this->y = y;
	this->counter = 0;
	this->isSwitch = false;
	this->isPutBox = false;
	this->isInjure = false;
	this->isDie = false;
	this->isComplete = false;

	this->loadResources();
	this->setState(CARRY_ARM_STATE_FLY);

	box = new Box(this->x - 6, this->y + 59);
	box->isNext = this->isNext;
	box->isLeft = this->isLeft;
}

CarryArm::~CarryArm()
{
}

void CarryArm::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	this->dt = dt;
	if (this->isDie) {
		generatePosition2();
		return;
	}
	if (this->isDamage) {
		generatePosition();
		this->isInjure = true;
	}

	if (isLeft) {
		if (counter > 50) {
			counter = 0;
			isSwitch = true;
			isPutBox = true;
		}

		if (isSwitch) {
			if (isPutBox) {
				if (this->isInjure) setState(CARRY_ARM_STATE_INJURE);
				else setState(CARRY_ARM_STATE_PUT_BOX);
				if (_animations[state]->isLastFrame()) {
					isPutBox = false;
				}
				speed.vx = 0;
				putBoxX = x - 6;
				putBoxY = y + 59;
			}
			else
			{
				if (this->isInjure) setState(CARRY_ARM_STATE_INJURE);
				else setState(CARRY_ARM_STATE_FLY);
			}

			speed.vx = -CARRY_ARM_SPEED_X;
			speed.vy = -CARRY_ARM_SPEED_Y;

			x += speed.vx * dt;
			y += speed.vy * dt;

			if (y <= 672) {
				isSwitch = false;
				speed.vx = 0;
				speed.vy = 0;
				x = initX;
				y = initY;
				this->isDamage = false;
				this->isComplete = true;
			}
			return;
		}

		if (y >= 720) {
			x += speed.vx * dt;
		}

		y += speed.vy * dt;

		if (!isNext) {
			if (x >= 4944 && x < 4985 + 25) {
				speed.vy = 0;
			}

			if (x >= 4985 + 25) {
				speed.vx = 0;
				speed.vy = CARRY_ARM_SPEED_Y;
			}
		}
		else
		{
			if (x >= 4944 + 25 && x < 4985 + 25 + 59) {
				speed.vy = 0;
			}

			if (x >= 4985 + 25 + 59) {
				speed.vx = 0;
				speed.vy = CARRY_ARM_SPEED_Y;
			}
		}

		if (y >= 820) {
			y = 820;
			counter++;
		}
	}
	else
	{
		if (counter > 50) {
			counter = 0;
			isSwitch = true;
			isPutBox = true;
		}

		if (isSwitch) {
			if (isPutBox) {
				if (this->isInjure) setState(CARRY_ARM_STATE_INJURE);
				else setState(CARRY_ARM_STATE_PUT_BOX);
				if (_animations[state]->isLastFrame()) {
					isPutBox = false;
				}
				speed.vx = 0;
				putBoxX = x - 6;
				putBoxY = y + 59;
			}
			else
			{
				if (this->isInjure) setState(CARRY_ARM_STATE_INJURE);
				else setState(CARRY_ARM_STATE_FLY);
			}

			speed.vx = -CARRY_ARM_SPEED_X;
			speed.vy = -CARRY_ARM_SPEED_Y;

			x += speed.vx * dt;
			y += speed.vy * dt;

			if (y <= 672) {
				isSwitch = false;
				speed.vx = 0;
				speed.vy = 0;
				x = initX;
				y = initY;
				this->isDamage = false;
				this->isComplete = true;
			}
			return;
		}

		if (y >= 720) {
			x -= speed.vx * dt;
		}

		y += speed.vy * dt;

		if (!isNext) {
			if (x <= 4985 + 25) {
				speed.vx = 0;
				speed.vy = CARRY_ARM_SPEED_Y;
			}
		}
		else
		{
			if (x <= 4985 + 25 + 59) {
				speed.vx = 0;
				speed.vy = CARRY_ARM_SPEED_Y;
			}
		}

		if (y >= 820) {
			y = 820;
			counter++;
		}
	}
	

	box->update(dt);
}

void CarryArm::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (this->isDie) {
		renderDie(dt);
		return;
	}

	if (this->isDamage) {
		renderDamage(dt);
	}

	auto center = cameraGlobal->transform(x, y);
	_animations[state]->render(center.x, center.y);

	box->render(dt);
}

void CarryArm::renderDamage(DWORD dt, D3DCOLOR colorBrush)
{
	for (int i = 0; i < 9; i++) {
		auto center = cameraGlobal->transform(damage[i].x, damage[i].y);
		_animations[CARRY_ARM_STATE_DESTROY + i]->render(center.x, center.y);
	}
}

void CarryArm::generatePosition()
{
	// init position
	damage[0] = { x, y }; //* important
	damage[1] = { x + 24, y };
	damage[2] = { x, y + 24 };
	damage[3] = { x + 48, y + 24 };
	damage[4] = { x + 24, y };
	damage[5] = { x, y + 24 };
	damage[6] = { x + 48, y + 24 };
	damage[7] = { x + 24, y };
	damage[8] = { x, y + 24 };
	damage[9] = { x + 48, y + 24 };

	vy += 0.01f * dt;
	vx += 0.008f * dt;

	dx = vx * dt;
	dy = vy * dt;

	damage[0].x -= dx * 1.25;
	damage[1].x += dx * 1.5;
	damage[2].x -= dx;
	damage[3].x += dx * 2.25;
	damage[4].x -= dx * 0.5;
	damage[5].x += dx * 1.5;
	damage[6].x -= dx;
	damage[7].x += dx * 2;
	damage[8].x -= dx;
	damage[9].x += dx * 1.5;


	damage[0].y += dy * 2;
	damage[1].y += dy;
	damage[2].y += dy * 2;
	damage[3].y += dy * 1.25;
	damage[4].y += dy;
	damage[5].y += dy * 2;
	damage[6].y += dy;
	damage[7].y += dy * 0.5;
	damage[8].y += dy * 2;
	damage[9].y += dy;
}

void CarryArm::renderDie(DWORD dt, D3DCOLOR colorBrush)
{
	for (int i = 0; i < 9; i++) {
		auto center = cameraGlobal->transform(die[i].x, die[i].y);
		_animations[CARRY_ARM_STATE_DIE + i]->render(center.x, center.y);
	}
}

void CarryArm::generatePosition2()
{
	// init position
	die[0] = { x, y }; //* important
	die[1] = { x + 24, y };
	die[2] = { x, y + 24 };
	die[3] = { x + 48, y + 24 };
	die[4] = { x + 24, y };
	die[5] = { x, y + 24 };
	die[6] = { x + 48, y + 24 };
	die[7] = { x + 24, y };
	die[8] = { x, y + 24 };
	die[9] = { x + 48, y + 24 };

	speed.vy += 0.01f * dt;
	speed.vx += 0.008f * dt;

	dx =speed. vx * dt;
	dy = speed.vy * dt;

	die[0].x -= dx * 1.25;
	die[1].x += dx * 1.5;
	die[2].x -= dx;
	die[3].x += dx * 2.25;
	die[4].x -= dx * 0.5;
	die[5].x += dx * 1.5;
	die[6].x -= dx;
	die[7].x += dx * 2;
	die[8].x -= dx;
	die[9].x += dx * 1.5;


	die[0].y += dy * 2;
	die[1].y += dy;
	die[2].y += dy * 2;
	die[3].y += dy * 1.25;
	die[4].y += dy;
	die[5].y += dy * 2;
	die[6].y += dy;
	die[7].y += dy * 0.5;
	die[8].y += dy * 2;
	die[9].y += dy;
}

void CarryArm::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
}



void CarryArm::setState(int state)
{
	switch (state)
	{
	case CARRY_ARM_STATE_FLY:
		speed.vx = CARRY_ARM_SPEED_X;
		speed.vy = CARRY_ARM_SPEED_Y;
		break;
	case CARRY_ARM_STATE_PUT_BOX:
		speed.vx = 0;
		speed.vy = 0;
		break;
	default:
		break;
	}
	this->state = state;
}

void CarryArm::loadResources()
{
	CTextures * textures = CTextures::getInstance();
	if (!textures->getTexture(CARRY_ARM_ID_TEXTURE))
		textures->add(CARRY_ARM_ID_TEXTURE, L"Resource\\Textures\\subboss.png", 0, 0, D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();

	LPANIMATION ani;

	// fly
	sprites->addSprite(20001, CARRY_ARM_ID_TEXTURE, 348, 94, 36, 59);
	sprites->addSprite(20002, CARRY_ARM_ID_TEXTURE, 388, 94, 36, 59);
	sprites->addSprite(20003, CARRY_ARM_ID_TEXTURE, 428, 94, 36, 59);
	sprites->addSprite(20004, CARRY_ARM_ID_TEXTURE, 468, 94, 36, 59);

	ani = new CAnimation(50);
	ani->add(20001);
	ani->add(20002);
	ani->add(20003);
	ani->add(20004);
	animations->add(CARRY_ARM_STATE_FLY, ani);

	// put box
	sprites->addSprite(20011, CARRY_ARM_ID_TEXTURE, 408, 163, 44, 57); // 44 x 57
	sprites->addSprite(20012, CARRY_ARM_ID_TEXTURE, 453, 163, 44, 57);
	sprites->addSprite(20013, CARRY_ARM_ID_TEXTURE, 498, 163, 44, 57);
	sprites->addSprite(20014, CARRY_ARM_ID_TEXTURE, 547, 163, 44, 57);
	sprites->addSprite(20015, CARRY_ARM_ID_TEXTURE, 595, 163, 44, 57);
	sprites->addSprite(20016, CARRY_ARM_ID_TEXTURE, 639, 163, 44, 57);

	ani = new CAnimation(50);
	ani->add(20011);
	ani->add(20012);
	ani->add(20013);
	ani->add(20014);
	ani->add(20015);
	ani->add(20016);
	animations->add(CARRY_ARM_STATE_PUT_BOX, ani);

	// injure
	sprites->addSprite(20021, CARRY_ARM_ID_TEXTURE, 518, 94, 32, 41);
	sprites->addSprite(20022, CARRY_ARM_ID_TEXTURE, 560, 94, 32, 41);
	sprites->addSprite(20023, CARRY_ARM_ID_TEXTURE, 599, 94, 32, 41);
	sprites->addSprite(20024, CARRY_ARM_ID_TEXTURE, 639, 94, 32, 41);
	sprites->addSprite(20025, CARRY_ARM_ID_TEXTURE, 681, 94, 32, 41);

	ani = new CAnimation(100);
	ani->add(20021);
	ani->add(20022);
	ani->add(20023);
	ani->add(20024);
	ani->add(20025);
	animations->add(CARRY_ARM_STATE_INJURE, ani);

	// destroy
	sprites->addSprite(20031, CARRY_ARM_ID_TEXTURE, 416, 45, 6, 7);
	sprites->addSprite(20032, CARRY_ARM_ID_TEXTURE, 431, 44, 6, 6);
	sprites->addSprite(20033, CARRY_ARM_ID_TEXTURE, 447, 44, 5, 7);
	sprites->addSprite(20034, CARRY_ARM_ID_TEXTURE, 464, 44, 5, 4);
	sprites->addSprite(20035, CARRY_ARM_ID_TEXTURE, 480, 45, 7, 6);
	sprites->addSprite(20036, CARRY_ARM_ID_TEXTURE, 496, 45, 6, 7);
	sprites->addSprite(20037, CARRY_ARM_ID_TEXTURE, 512, 44, 5, 7);
	sprites->addSprite(20038, CARRY_ARM_ID_TEXTURE, 528, 45, 6, 6);
	sprites->addSprite(20039, CARRY_ARM_ID_TEXTURE, 543, 46, 7, 4);
	sprites->addSprite(20040, CARRY_ARM_ID_TEXTURE, 560, 45, 6, 4);

	for (int i = 0; i < 9; i++)
	{
		ani = new CAnimation(100);
		ani->add(20031 + i);
		animations->add(CARRY_ARM_STATE_DESTROY + i, ani);
		this->addAnimation(CARRY_ARM_STATE_DESTROY + i);
	}

	// die
	sprites->addSprite(20041, CARRY_ARM_ID_TEXTURE, 599, 14, 7, 12);
	sprites->addSprite(20042, CARRY_ARM_ID_TEXTURE, 617, 12, 12, 7);
	sprites->addSprite(20043, CARRY_ARM_ID_TEXTURE, 447, 44, 5, 7);
	sprites->addSprite(20044, CARRY_ARM_ID_TEXTURE, 464, 44, 5, 4);
	sprites->addSprite(20045, CARRY_ARM_ID_TEXTURE, 480, 45, 7, 6);
	sprites->addSprite(20046, CARRY_ARM_ID_TEXTURE, 496, 45, 6, 7);
	sprites->addSprite(20047, CARRY_ARM_ID_TEXTURE, 512, 44, 5, 7);
	sprites->addSprite(20048, CARRY_ARM_ID_TEXTURE, 528, 45, 6, 6);
	sprites->addSprite(20049, CARRY_ARM_ID_TEXTURE, 543, 46, 7, 4);
	sprites->addSprite(20050, CARRY_ARM_ID_TEXTURE, 560, 45, 6, 4);

	for (int i = 0; i < 9; i++)
	{
		ani = new CAnimation(100);
		ani->add(20041 + i);
		animations->add(CARRY_ARM_STATE_DIE + i, ani);
		this->addAnimation(CARRY_ARM_STATE_DIE + i);
	}

	// add animations
	this->addAnimation(CARRY_ARM_STATE_FLY);
	this->addAnimation(CARRY_ARM_STATE_PUT_BOX);
	this->addAnimation(CARRY_ARM_STATE_INJURE);
}
