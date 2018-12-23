#include "CarryArm.h"


CarryArm::CarryArm(int id, float x, float y)
{
	this->_id = id;
	this->x = x;
	this->y = y;
	this->counter = 0;
	this->isSwitch = false;
	this->isLeft = true;
	this->isPutBox = false;

	this->loadResources();
	this->setState(CARRY_ARM_STATE_FLY);
}

CarryArm::~CarryArm()
{
}

void CarryArm::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	if (counter > 50) {
		counter = 0;
		isSwitch = true;
		isPutBox = true;
	}

	if (isSwitch) {
		if (isPutBox) {
			setState(CARRY_ARM_STATE_PUT_BOX);
			if (_animations[state]->isLastFrame()) {
				isPutBox = false;
			}
			speed.vx = 0;
		}
		else
		{
			setState(CARRY_ARM_STATE_FLY);
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
		}
		return;
	}

	if (y >= 750) {
		x += speed.vx * dt;
	}

	y += speed.vy * dt;

	if (x >= 4944 && x < 4985 + 25) {
		speed.vy = 0;
	}

	if (x >= 4985 + 25) {
		speed.vx = 0;
		speed.vy = CARRY_ARM_SPEED_Y;
	}

	if (y >= 830) {
		y = 830;
		counter++;
	}
}

void CarryArm::render(DWORD dt, D3DCOLOR colorBrush)
{
	auto center = cameraGlobal->transform(x, y);
	_animations[state]->render(center.x, center.y);
}

void CarryArm::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

CarryArm* CarryArm::clone(int id, int x, int y)
{
	return nullptr;
}

void CarryArm::setState(int state)
{
	switch (state)
	{
	case CARRY_ARM_STATE_FLY:
	case CARRY_ARM_STATE_PUT_BOX:
		speed.vx = CARRY_ARM_SPEED_X;
		speed.vy = CARRY_ARM_SPEED_Y;
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

	// die
	sprites->addSprite(20031, CARRY_ARM_ID_TEXTURE, 119, 94, 144, 88);

	ani = new CAnimation(100);
	ani->add(20031);
	animations->add(CARRY_ARM_STATE_DIE, ani);

	// add animations
	this->addAnimation(CARRY_ARM_STATE_FLY);
	this->addAnimation(CARRY_ARM_STATE_PUT_BOX);
	this->addAnimation(CARRY_ARM_STATE_INJURE);
	this->addAnimation(CARRY_ARM_STATE_DIE);
}
