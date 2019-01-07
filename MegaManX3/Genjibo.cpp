#include "Genjibo.h"

Genjibo::Genjibo()
{	
}
Genjibo::~Genjibo()
{
}

void Genjibo::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	if (!visible)
	{
		return;
	}
	else
	{
		GameObject::update(dt);
		timeWaiting.update();
		if (y < 690) 
		{
			visible = false;
			return;
		}
		if (y >= 880 && !dropShurikein)
		{
			timeWaiting.start();
			dropShurikein = true;
		}
		if (timeWaiting.isRunning() && y >= 880)
		{
			speed.vx = 0.0f;
			speed.vy = 0.0f;
			if (!obj->visible)
			{
				obj->visible = true;
				obj->state = manifest;
			}
		}
		else if (!dropShurikein)
		{
			speed.vx = 0.0f;
			speed.vy = 0.18f;
		}
		else
		{
			speed.vx = 0.0f;
			speed.vy = -0.18f;
			if (!obj->enable)
				obj->enable = true;
		}
		x += dx;
		y += dy;
	}

}

void Genjibo::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (!visible) return;
	auto pos = cameraGlobal->transform(x, y);
	_animations[fly]->render(pos.x, pos.y, true, WHITE(255));
	_animations[jet]->renderFlipX(pos.x - 12, pos.y,false, WHITE(255));
	_animations[jet]->render(pos.x + 7, pos.y, false, WHITE(255));
	if (timeWaiting.isRunning())
	{
		_animations[illuminate]->render(pos.x + 0, pos.y + 34, true, WHITE(255));
	}
}

void Genjibo::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

Genjibo::Genjibo(UINT id, float x, float y, float vx, float vy)
{
	loadResources();
	this->x = x;
	this->y = y;
}

void Genjibo::setShurikein(Shurikein * obj)
{
	this->obj = obj;
}

void Genjibo::loadResources()
{
		if(!texturesGlobal->getTexture(TShurikein))
		texturesGlobal->add(TShurikein, L"Resource\\Textures\\Shurikein.png", 555, 468, D3DCOLOR_XRGB(64, 48, 72));
#pragma region fly
		auto ani = new CAnimation(50);
		spritesGlobal->add(fly, TShurikein, 126, 10, 147, 33);
		spritesGlobal->add(fly + 1, TShurikein, 166, 10, 187, 33);
		spritesGlobal->add(fly + 2, TShurikein, 206, 10, 227, 33);
		spritesGlobal->add(fly + 3, TShurikein, 246, 10, 267, 33);

		for (int i = 0; i < 4; i++)
		{
			ani->add(fly + i);
		}
		_animations[fly] = ani;
#pragma endregion
#pragma region jet
		ani = new CAnimation(50);
		spritesGlobal->addSprite(jet, TShurikein, 131, 44, 8, 8);
		spritesGlobal->addSprite(jet + 1, TShurikein, 147, 44, 8, 8);
		spritesGlobal->addSprite(jet + 2, TShurikein, 161, 42, 8, 8);
		spritesGlobal->addSprite(jet + 3, TShurikein, 178, 41, 8, 8);
		spritesGlobal->addSprite(jet + 4, TShurikein, 196, 42, 8, 8);
		for (int i = 0; i < 5; i++)
		{
			ani->add(jet + i);
		}
		_animations[jet] = ani;
#pragma endregion
#pragma region illuminate 
		ani = new CAnimation(100);
		spritesGlobal->addSprite(illuminate, TShurikein, 281, 10, 31, 48);
		ani->add(illuminate);
		_animations[illuminate] = ani;
#pragma endregion



}