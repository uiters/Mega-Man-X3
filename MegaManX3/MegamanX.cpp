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
	effect = new MegamanEffectFactory();
	keyController = new KeyController(this, effect, false);
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
	GameObject::update(dt);

	speed.vy += 0.0012f * dt; ////

	collisionStatic(staticObjects);
	collisionDynamic(dynamicObjects);
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
	updateState(dt);
	Point center = { 0, 0 };
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
	//D3DXMATRIX matScale;
	//D3DXMATRIX oldMatrix;
	//D3DXMatrixScaling(&matScale, 0.9f, 0.9f, .0f);

	
	auto spriteHandler = gameGlobal->getSpriteHandler();
	
	//spriteHandler->GetTransform(&oldMatrix);
	//spriteHandler->SetTransform(&matScale);

	//spriteHandler->End();
	//spriteHandler->Begin(D3DXSPRITE_DONOTSAVESTATE);
	
	if (isFlipX)
		_animations[state]->renderFlipX(center.x, center.y, false, colorBrush);
	else
		_animations[state]->render(center.x, center.y, false, colorBrush);
	
	//spriteHandler->End();
	//spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	//spriteHandler->SetTransform(&oldMatrix);
	effect->render(dt);
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

