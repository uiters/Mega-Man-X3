#include "MegamanX.h"
#include "Elevator.h"
#include "ConstGlobals.h"
#include <vector>

void MegamanX::collisionStatic(unordered_map<int, GameObject*>* staticObjects)
{
	vector<CollisionEvent*> coEvents;
	vector<CollisionEvent*> coEventsResult;
	
	collision->findCollisions(dt, this, *staticObjects, coEvents);
	UINT size = coEvents.size();
	if (size == 0)
	{
		x += dx;
		y += dy;
		return;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		collision->filterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 1.f;
		y += min_ty * dy + ny * 1.f;
		
		if (nx != 0) speed.vx = 0;
		if (ny != 0) speed.vy = 0;
		//else keyController->setFloor(null);


		
		for (UINT i = 0; i < coEventsResult.size(); ++i)
		{
			auto e = coEventsResult[i];
			StaticObject* obj = dynamic_cast<StaticObject *>(e->obj);
			if (obj)
			{
				if (e->ny < 0)
				{
					keyController->stopFallOrSlide();
					keyController->setFloor(obj);
				}
				else if(e->ny > 0)
				{
					keyController->stopJump();
					keyController->setFloor(obj);
				}
				else if (e->nx !=0)
				{
					keyController->stopDash();
					keyController->setNearWall(e->nx > 0, obj);
				}
				obj->run();
			}
		}
	}
	keyController->update();

	
}

void MegamanX::collisionDynamic(unordered_map<int, GameObject*>* dynamicObjects)
{
	bulletCollisionDynamic(dynamicObjects);//like main bullet collision dynamic
	if (isProtect) return;
	dynamicCollisionThis(dynamicObjects); //like dynamic obejct bullet collision this
}

void MegamanX::setHurt()
{
	isHurt = true;
	isProtect = true;
	keyController->setHurt(true);
	timeHurt.start();
	timeProtect.start();
	delay = 3;
}

MegamanX::MegamanX(UINT idTexture, float x, float y, float vx, float vy) :DynamicObject(idTexture, x, y, vx, vy)
{
	weapon = new MegamanWeapon(&_weapons);
	effect = new MegamanEffectFactory();
	keyController = new KeyController(this, effect, weapon, false);
	width = Stand_Shoot_Width;
	height = Stand_Shoot_Height;
}

MegamanX::~MegamanX()
{
}




MegamanX * MegamanX::clone(int id, int x, int y)
{
	return nullptr;
}

void MegamanX::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	if (_death) return;
	GameObject::update(dt);

	speed.vy += 0.0012f * dt;

	collisionStatic(staticObjects);
	collisionDynamic(dynamicObjects);

	if (isProtect)
	{
		timeProtect.update();
		
		if (timeHurt.isRunning())
		{
			timeHurt.update();
		}
		else isHurt = false, keyController->setHurt(false);

		delay -= 1;
		if (timeProtect.isStop()) isProtect = false;
	}

	weapon->update(dt);

}

void MegamanX::updateState(DWORD dt) 
{
	int statePre = keyController->getState(isFlipX);
	if (state != statePre && (statePre == dash || statePre == run || statePre == jump || statePre == run_shoot))
	{
		_animations[statePre]->reset();
	}
	state = statePre;
}

void MegamanX::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (_death)
	{
		if (timePreDie.isRunning())
		{
			timePreDie.update();
			auto pos = cameraGlobal->transform(x, y);
			_animations[preDie]->render(pos.x, pos.y);
			return;
		}
		countDissapear.update();
		if (countDissapear.isStop())
		{
			resetPoint();
			countDissapear.start();
		}
		dissapear(dt, colorBrush);
		return;
	}
	updateState(dt);
	
	if (!isHurt && isProtect)
	{
		colorBrush = showblur ? WHITE(128) : WHITE(255);
		if (delay < 0) delay = 3, showblur = !showblur; //delay two frames 
	}


	Point center = { 0, 0 };
	config(center);
	auto spriteHandler = gameGlobal->getSpriteHandler();
	if (isFlipX)
		_animations[state]->renderFlipX(center.x, center.y, false, colorBrush);
	else
		_animations[state]->render(center.x, center.y, false, colorBrush);

	effect->render(dt, x, y, width, height);
	weapon->render(dt);
}

void MegamanX::dissapear(DWORD dt, D3DCOLOR colorBrush)
{
	
	speed.vx = 0.2;
	speed.vy = -0.2;
	p1.x += speed.vx*dt;
	p1.y += speed.vy*dt;
	auto pos = cameraGlobal->transform(p1.x, p1.y);
	_animations[die]->render(pos.x, pos.y, colorBrush);

	speed.vx = 0.2;
	speed.vy = 0.2;
	p2.x += speed.vx*dt;
	p2.y += speed.vy*dt;
	pos = cameraGlobal->transform(p2.x, p2.y);
	_animations[die]->render(pos.x, pos.y, colorBrush);
	
	speed.vx = -0.2;
	speed.vy = 0.2;
	p3.x += speed.vx*dt;
	p3.y += speed.vy*dt;
	pos = cameraGlobal->transform(p3.x, p3.y);
	_animations[die]->render(pos.x, pos.y, colorBrush);

	speed.vx = -0.2;
	speed.vy = -0.2;
	p4.x += speed.vx*dt;
	p4.y += speed.vy*dt;
	pos = cameraGlobal->transform(p4.x, p4.y);
	_animations[die]->render(pos.x, pos.y, colorBrush);

	speed.vx = 0.2;
	speed.vy = 0;
	p5.x += speed.vx*dt;
	p5.y += speed.vy*dt;
	pos = cameraGlobal->transform(p5.x, p5.y);
	_animations[die]->render(pos.x, pos.y, colorBrush);

	speed.vx = 0;
	speed.vy = 0.2;
	p6.x += speed.vx*dt;
	p6.y += speed.vy*dt;
	pos = cameraGlobal->transform(p6.x, p6.y);
	_animations[die]->render(pos.x, pos.y, colorBrush);

	speed.vx = -0.2;
	speed.vy = 0;
	p7.x += speed.vx*dt;
	p7.y += speed.vy*dt;
	pos = cameraGlobal->transform(p7.x, p7.y);
	_animations[die]->render(pos.x, pos.y, colorBrush);

	speed.vx = 0;
	speed.vy = -0.2;
	p8.x += speed.vx*dt;
	p8.y += speed.vy*dt;
	pos = cameraGlobal->transform(p8.x, p8.y);
	_animations[die]->render(pos.x, pos.y, colorBrush);
}

void MegamanX::resetPoint()
{
	p1 = { x, y - 10 };
	p2 = { x + 10, y };
	p3 = { x, y + 10 };
	p4 = { x - 10, y };
	p5 = { x + 10, y - 10 };
	p6 = { x + 10 , y + 10 };
	p7 = { x - 10 , y + 10 };
	p8 = { x - 10, y - 10 };
}

void MegamanX::config(Point & center)
{
	switch (state)
	{
	case dash:
	case dash_shoot:
		center = cameraGlobal->transform(x, y + 9);////
		break;
	case slide:
	case cling:
		int deta;
		(isFlipX) ? deta = -1 : deta = 6;
		center = cameraGlobal->transform(x + deta, y);////
		break;
	case slide_shoot:
	case cling_shoot:
		(isFlipX) ? deta = -1 : deta = 1;
		center = cameraGlobal->transform(x + deta, y);
		break;
	default:
		center = cameraGlobal->transform(x, y);
		break;
	}
}

void MegamanX::onKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_LEFT:
		keyController->addKeyArrow(true);
		break;
	case DIK_RIGHT:
		keyController->addKeyArrow(false);
		break;
	case DIK_Z:
		keyController->addKeyZ();
		break;
	case DIK_X:
		keyController->addKeyX();
		break;
	case DIK_C:
		keyController->addKeyC();
		break;
	default:
		break;
	}
}

void MegamanX::onKeyUp(int keyCode)
{
	switch (keyCode)
	{
	case DIK_LEFT:
		keyController->removeKeyArrow(true);
		break;
	case DIK_RIGHT:
		keyController->removeKeyArrow(false);
		break;
	case DIK_Z:
		keyController->removeKeyZ();
		break;
	case DIK_X:
		keyController->removeKeyX();
		break;
	case DIK_C:
		keyController->removeKeyC();
		break;
	default:
		break;
	}
}

void MegamanX::keyState(BYTE *_state)
{
	keyController->update();
}

void MegamanX::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	keyController->getSize(width, height);
	right = x + width;
	bottom = height + y;

}

void MegamanX::dynamicCollisionThis(unordered_map<int, GameObject*>* dynamicObjects)
{
	auto megamanBox = this->getBoundBox();
	for (auto kv : *dynamicObjects)
	{
		// object collision main (include bullet) (use single & swept aabb)
		DynamicObject* obj = dynamic_cast<DynamicObject*>(kv.second);
		if (!obj || obj->isDeath()) continue;

		if (kv.second->getBoundBox().intersectsWith(megamanBox) //single
			||
			collisionGameObject(obj, this)) // swpet
		{
			setHurt();
			return;
		}

		auto bullets = obj->getWeapons();
		for (auto bullet = bullets->begin(); bullet != bullets->end(); )
		{
			if (bullet[0]->getBoundBox().intersectsWith(megamanBox) //single
				||
				collisionBullet(obj, *bullet, this)) //swept
			{
				if (bullet[0]->toLeft)
					obj->createExplosion(bullet[0]->x + 10, bullet[0]->y);
				else
					obj->createExplosion(bullet[0]->x - 10, bullet[0]->y);
				delete *bullet;
				bullet = bullets->erase(bullet);
				setHurt();
				return;
			}
			else ++bullet;
		}
	}
}

void MegamanX::bulletCollisionDynamic(unordered_map<int, GameObject*>* dynamicObjects)
{
	for(auto it = dynamicObjects->begin(); it!= dynamicObjects->end(); )
	{
		DynamicObject* obj = dynamic_cast<DynamicObject*>((*it).second);
		if (!obj)
		{
			++it;
			continue;
		}
		// bullet main collision enemies or boss (use single & swept aabb)
		auto objBox = obj->getBoundBox();
		for (auto bullet = _weapons.begin(); bullet != _weapons.end();)
		{
			if (obj->isDeath()) break;
			if (bullet[0]->getBoundBox().intersectsWith(objBox) //single aabb collision
				||
				collisionGameObject(*bullet, obj)) //colision bullet with dynamic with swept aabb
			{
				obj->receiveDamage(bullet[0]->getDamage());
				if (obj->isDeath())
				{
					if (dynamic_cast<BusterShot*>(*bullet)) // don't cross delete bullet
					{
						delete *bullet;
						bullet = _weapons.erase(bullet);
					}
				}
				else
				{
					delete *bullet;
					bullet = _weapons.erase(bullet);
				}
				break;// out for bullet
			}
			else // bullet main collision bullet enemies or boss (use swept aabb)
			{
				auto dynamicBullets = obj->getWeapons();
				bool noDelete = true;
				for (auto bulletDynamic = dynamicBullets->begin(); bulletDynamic != dynamicBullets->end();)
				{
					if (collisionBullet(obj, *bulletDynamic, *bullet))
					{
						if (bulletDynamic[0]->toLeft)
							obj->createExplosion(bulletDynamic[0]->x + 10, bulletDynamic[0]->y);
						else
							obj->createExplosion(bulletDynamic[0]->x - 10, bulletDynamic[0]->y);

						delete bulletDynamic[0];
						bulletDynamic = dynamicBullets->erase(bulletDynamic);
						noDelete = false;
						if (dynamic_cast<BusterShot*>(*bullet)) // don't cross delete bullet
						{
							delete *bullet,
							bullet = _weapons.erase(bullet);
						}
						else ++bullet;
						break;
					}
					else ++bulletDynamic;
				}
				if (noDelete) ++bullet;
			}
		}

		++it;
	}
}

bool MegamanX::collisionGameObject(GameObject* obj1, GameObject* obj2)
{
	auto e = collision->sweptAABBEx(dt, obj1, obj2);
	if (e->t > 0 && e->t <= 1.0f)
	{
		delete e;
		return true;
	}
	delete e;
	return false;
}

bool MegamanX::collisionBullet(DynamicObject* obj1, Weapon* bullet1, GameObject* obj2)
{
	auto e = Collision::getInstance()->sweptAABBEx(dt, bullet1, obj2);
	if (e->t > 0 && e->t <= 1.0f)
	{
		delete e;
		return true;
	}
	delete e;
	return false;
}

