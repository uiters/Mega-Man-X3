#include "Helit.h"
#pragma region Load
void Helit::loadSprites()
{
	if (!spritesGlobal->get(HelitAnimation))
	{
		spritesGlobal->addSprite(HelitAnimation, THelit, 5, 2, 17, 8);
		spritesGlobal->addSprite(HelitAnimation + 1, THelit, 23, 2, 27, 8);
		spritesGlobal->addSprite(HelitAnimation + 2, THelit, 52, 2, 39, 8);
		spritesGlobal->addSprite(HelitAnimation + 3, THelit, 93, 2, 27, 8);
		spritesGlobal->addSprite(HelitAnimation + 4, THelit, 122, 2, 17, 8);

		spritesGlobal->addSprite(HelitBody1, THelit, 5, 23, 24, 29);
		spritesGlobal->addSprite(HelitBody2, THelit, 35, 23, 24, 29);

		spritesGlobal->addSprite(HelitDie, THelit, 96, 26, 26, 8);
		spritesGlobal->addSprite(HelitDie + 1, THelit, 123, 23, 12, 17);
		spritesGlobal->addSprite(HelitDie + 2, THelit, 138, 17, 17, 23);

		spritesGlobal->addSprite(HelitBulletAnimation, THelit, 68, 33, 15, 10);
	}
}

void Helit::loadResources()
{
	loadSprites();

#pragma region Animation Head
	auto ani = new CAnimation(50);
	ani->add(HelitAnimation);
	ani->add(HelitAnimation + 1);
	ani->add(HelitAnimation + 2);
	ani->add(HelitAnimation + 3);
	ani->add(HelitAnimation + 4);
	_animations[HelitAnimation] = ani;

#pragma endregion

#pragma region Body
	ani = new CAnimation(5000);
	ani->add(HelitBody1);
	_animations[HelitBody1] = ani;

	ani = new CAnimation(5000);
	ani->add(HelitBody2);
	_animations[HelitBody2] = ani;

	body = HelitBody1;
#pragma endregion

#pragma region Die
	for (int i = 0; i < 3; ++i)
	{
		ani = new CAnimation(100);
		ani->add(HelitDie + i);
		_animations[HelitDie + i] = ani;
	}

#pragma endregion


}

#pragma endregion

#pragma region Coontructor

Helit::Helit(int id, float x, float y, bool toLeft) : DynamicObject(id, x, y, 0, 0)
{
	initDamage = 2.f;
	_effects.emplace_back(WallSlide::getInstance());
	_effects.emplace_back(ExplosionEffect::getInstance());

	this->toLeft = toLeft;
	this->initToLeft = toLeft;
	loadResources();

	timeFire.start();

	initHP = _hp = 2;
	setResetBound();
}

void Helit::setResetBound()
{
	resetBound.x = x;
	resetBound.y = y;
	resetBound.width = 22;
	resetBound.height = 30;
}
#pragma endregion



void Helit::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 22;
	bottom = y + 30;
}


void Helit::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	this->dt = dt;
	updateWeapon(dt, staticObjects);

	if (!visible) return;

	if (_death)
	{
		calculateDie();
	}
	else
	{
		timeFire.update();
		if (timeFire.isStop())
		{
			setAnimationFire();
			timeFire.start();
		}
		if (body == HelitBody2 && --timeSwitchBody == 0)
			body = HelitBody1, toLeft = !toLeft;
	}
}

void Helit::render(DWORD dt, D3DCOLOR colorBrush)
{
	_effects[HELIT_EFFECT_EXPLOSION]->render(dt, true);
	renderWeapon(dt, colorBrush);

	if (visible)
	{
		if (_death) 
		{
			renderDie(dt);
		}
		else
		{
			renderNormal(dt);
		}
		
	}
}

Helit::~Helit()
{
	for (int i = 0; i < _animations.size(); ++i)
	{
		delete _animations[i];
	}
}


void Helit::calculateDie()
{
	speed.vy += 0.00115f * dt;
	speed.vx += 0.000125 *dt;

	dx = speed.vx * dt;
	dy = speed.vy * dt;

	dieX[0].x += dx;
	dieX[1].x += dx * 2;
	dieX[2].x -= dx;

	dieX[0].y += dy;
	dieX[1].y += dy;
	dieX[2].y += dy;

	//debugOut(L"%f %f %f %f %f %f ", dieX[0].x, dieX[0].y);
}

void Helit::setAnimationDie()
{
	_death = true;
	dieX[0] = dieX[1] = dieX[2] = { x, y };
	speed.vy = -0.0125f *dt;
	speed.vx = 0.0002f * dt;
	this->showColor = true;
	timeSwitchColor = 0;
	createExplosion(x + 10, y);
}

void Helit::renderDie(DWORD dt)
{
	for (int i = 0; i < 3; ++i)
	{
		auto pos = cameraGlobal->transform(dieX[i].x, dieX[i].y);
		_animations[HelitDie + i]->render(pos.x, pos.y, true, this->showColor ? WHITE(100) : WHITE(255));
	}
	if (++timeSwitchColor == 2)
		showColor = !showColor, timeSwitchColor = 0;
}


void Helit::renderNormal(DWORD dt)
{
	auto pos = cameraGlobal->transform(x, y);
	if (toLeft)
	{
		_animations[body]->render(pos.x, pos.y);
	}
	else
	{
		_animations[body]->renderFlipX(pos.x, pos.y);
	}
	_animations[HelitAnimation]->render(pos.x + 11.35f, pos.y - 3.25f, true);
	
	_effects[HELIT_EFFECT_FIRE]->render(dt, true);	
}

void Helit::setAnimationFire()
{
	if (toLeft)
		_weapons.emplace_back(new HelitBullet(x + 7, y + 20, toLeft)),
		_effects[HELIT_EFFECT_FIRE]->createEffect(x + 10, y + 22.2f);
	else
		_weapons.emplace_back(new HelitBullet(x + 3, y + 20, toLeft)), 
		_effects[HELIT_EFFECT_FIRE]->createEffect(x + 10, y + 22.2f);
	timeSwitchBody = 15;
	body = HelitBody2;
	
}


void Helit::updateWeapon(DWORD dt, unordered_map<int, GameObject*>* staticObjects)
{
	for (auto it = _weapons.begin(); it != _weapons.end();)
	{
		it[0]->update(dt);

		if (!it[0]->getBoundBox().intersectsWith(cameraGlobal->viewport))
		{
			delete (*it);
			it = _weapons.erase(it);
		}
		else 
		{
			if (collisionBulletStatic(it[0], staticObjects))
			{
				createExplosion(it[0]->x, it[0]->y);
				delete it[0];
				it = _weapons.erase(it);
			}else
				++it;
		}
	}
}

bool Helit::collisionBulletStatic(Weapon* bullet, unordered_map<int, GameObject*>* staticObjects)
{
	vector<CollisionEvent*> coEvents;
	vector<CollisionEvent*> coEventsResult;
	collision->findCollisions(dt, bullet, *staticObjects, coEvents);
	if (coEvents.size())
	{
		for (UINT i = 0; i < coEvents.size(); ++i) delete coEvents[i];
		return true;
	}
	else
	{
		return false;
	}
}

void Helit::createExplosion(float x, float y)
{
	_effects[HELIT_EFFECT_EXPLOSION]->createEffect(x, y);
}

