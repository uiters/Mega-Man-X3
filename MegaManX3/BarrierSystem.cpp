#include "BarrierSystem.h"



BarrierSystem::BarrierSystem()
{
	this->x = 4985;
	this->y = 692; // 692 -> 770
	this->initX = 4856;
	this->initY = 692;
	this->isHidden = false;
		
	this->setState(BARRIER_SYSTEM_SPEED_PART_1);
	this->loadResources();

	carryArm = new CarryArm(this->_id, initX + 36, initY - 20);
}


BarrierSystem::~BarrierSystem()
{
}

void BarrierSystem::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	if (this->isHidden == true) {
		if (state == BARRIER_SYSTEM_STATE_PART_2) {
			y -= speed.vy * dt;
			if (y <= 770) {
				y = 692;
				this->setState(BARRIER_SYSTEM_STATE_PART_1);
			}
		}
		else
		{
			initY -= speed.vy * dt;
			if (initY <= 692) {
				initY = 692;
			}
		}
		return;
	}

	if (state == BARRIER_SYSTEM_STATE_PART_1) {
		initY += speed.vy * dt;
		if (initY >= 770) {
			initY = 770;
			this->setState(BARRIER_SYSTEM_STATE_PART_2);
			y = 770;
		}
	}
	else
	{
		y += speed.vy * dt;
		if (y >= 855) {
			y = 855;
			carryArm->update(dt);
		}
	}
}

void BarrierSystem::render(DWORD dt, D3DCOLOR colorBrush)
{		
	auto center = cameraGlobal->transform(x, y);
	_animations[BARRIER_SYSTEM_STATE_PART_2]->render(center.x, center.y);

	center = cameraGlobal->transform(initX, initY);
	_animations[BARRIER_SYSTEM_STATE_PART_1]->render(center.x, center.y);

	carryArm->render(dt);
}

void BarrierSystem::setState(int state)
{
	switch (state)
	{
	case BARRIER_SYSTEM_STATE_PART_1:
		speed.vy = BARRIER_SYSTEM_SPEED_PART_1;
		break;
	case BARRIER_SYSTEM_STATE_PART_2:
		speed.vy = BARRIER_SYSTEM_SPEED_PART_2;
		break;
	default:
		break;
	}
	this->state = state;
}

void BarrierSystem::loadResources()
{
	CTextures * textures = CTextures::getInstance();
	if (!textures->getTexture(BARRIER_SYSTEM_ID_TEXTURE))
		textures->add(BARRIER_SYSTEM_ID_TEXTURE, L"Resource\\Textures\\subboss.png", 0, 0, D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::getInstance();
	CAnimations * animations = CAnimations::getInstance();

	LPANIMATION ani;

	// part 1
	sprites->addSprite(20001, BARRIER_SYSTEM_ID_TEXTURE, 7, 3, 256, 88);

	ani = new AnimationOneTime(100);
	ani->add(20001);
	animations->add(BARRIER_SYSTEM_STATE_PART_1, ani);

	// part 2
	sprites->addSprite(20002, BARRIER_SYSTEM_ID_TEXTURE, 119, 94, 144, 88);

	ani = new AnimationOneTime(100);
	ani->add(20002);
	animations->add(BARRIER_SYSTEM_STATE_PART_2, ani);

	// add animations
	this->addAnimation(BARRIER_SYSTEM_STATE_PART_1);
	this->addAnimation(BARRIER_SYSTEM_STATE_PART_2);
}

BarrierSystem * BarrierSystem::clone(int id, int x, int y)
{
	return nullptr;
}

void BarrierSystem::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

