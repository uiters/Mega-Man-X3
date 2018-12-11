#include "MegamanX.h"
#include "Elevator.h"
#include "ConstGlobals.h"


void MegamanX::collisionStatic(unordered_map<int, CTreeObject*>* staticObjects)
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

	for (UINT i = 0; i < size; ++i) delete coEvents[i];
}

void MegamanX::collisionDynamic(unordered_map<int, CTreeObject*>* dynamicObjects)
{

}

MegamanX::MegamanX(UINT idTexture, float x, float y, float vx, float vy) :DynamicObject(idTexture, x, y, vx, vy)
{
	weapon = new MegamanWeapon();
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

void MegamanX::update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects)
{
	if (_death) return;
	GameObject::update(dt);

	speed.vy += 0.0015f * dt;

	collisionStatic(staticObjects);
	collisionDynamic(dynamicObjects);
	weapon->update(dt);
	if (x > 1500)
	{
		_death = true;
		timePreDie.start();
	}
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
	int add = 0;
	switch (state)
	{
	case dash:
	case dash_shoot:
		add = 8;
		break;
	case slide:
	case slide_shoot:
	case cling:
	case cling_shoot:
		add = -12;
		break;
	default:
		break;
	}
	//D3DXMATRIX matScale;
	//D3DXMATRIX oldMatrix;
	//D3DXMatrixScaling(&matScale, 0.9f, 0.9f, .0f);

	
	auto spriteHandler = gameGlobal->getSpriteHandler();
	
	//spriteHandler->GetTransform(&oldMatrix);
	//spriteHandler->SetTransform(&matScale);

	//spriteHandler->End();
	//spriteHandler->Begin(D3DXSPRITE_DONOTSAVESTATE);
	auto center = cameraGlobal->transform(x, y + add);
	if (isFlipX)
		_animations[state]->renderFlipX(center.x, center.y, false, colorBrush);
	else
		_animations[state]->render(center.x, center.y, false, colorBrush);
	
	//spriteHandler->End();
	//spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	//spriteHandler->SetTransform(&oldMatrix);
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

