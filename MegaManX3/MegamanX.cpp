#include "MegamanX.h"

#include "ConstGlobals.h"


void MegamanX::collisionStatic(unordered_map<int, CTreeObject*>* staticObjects)
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
		
		if (nx != 0) speed.vx = 0;
		if (ny != 0) speed.vy = 0;

		
		for (UINT i = 0; i < coEventsResult.size(); ++i)
		{
			auto e = coEventsResult[i];
			Brick* obj = dynamic_cast<Brick *>(e->obj);
			if (obj)
			{
				if (e->ny < 0)
				{
					keyController->stopFallOrSlide();
				}
				else if(e->ny > 0)
				{
					keyController->stopJump();
				}
				else if (e->nx !=0)
				{
					keyController->stopDash();
					keyController->setNearWall(e->nx > 0, obj);
					debugOut(L"Here\n");
				}
			}
		}
	}
	keyController->update();
	UINT size = coEvents.size();
	for (UINT i = 0; i < size; ++i) delete coEvents[i];
}

void MegamanX::collisionDynamic(unordered_map<int, CTreeObject*>* dynamicObjects)
{
	
}

MegamanX::MegamanX(UINT idTexture, float x, float y, float vx, float vy) :DynamicObject(idTexture, x, y, vx, vy)
{
	keyController = new KeyController(this, false);
	//state = stand;
	//onAir = true;
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



	speed.vy += 0.0015f * dt;

	

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
	//switch (state)
	//{
	//case stand:
	//case shoot:
	//	speed.vx = 0;
	//	//speed.vy = 0;
	//	break;
	//case cling:
	//case cling_shoot:
	//	//x += isFlipX ? 0.05f * dt : -0.05f * dt;
	//	speed.vy = -0.0046f * dt;
	//	break;
	//case run:
	//case run_shoot:
	//	(isFlipX) ? speed.vx = -0.15f : speed.vx = 0.15f;
	//	break;
	//case dash:
	//case dash_shoot:
	//	(isFlipX) ? speed.vx = -0.01f * dt : speed.vx = 0.01f * dt;
	//	speed.vy = 0;
	//	break;
	//case jump:
	//	//(isFlipX) ? speed.vx = -0.15f : speed.vx = 0.15f;
	//	speed.vy += -0.0046f * dt;
	//	break;
	//case fall:
	//case fall_shoot:
	//	//speed.vy += 0.0001f * dt;
	//	break;
	//case shock:
	//	speed.vx = 0;
	//	speed.vy = 0;
	//	break;
	//default:
	//	break;
	//}
}

void MegamanX::render(DWORD dt, D3DCOLOR colorBrush)
{
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
	// khởi tạo ma trận phóng to theo trục Ox 2 lần, trục Oy 3 lần.
	//D3DXMatrixScaling(&matScale, 0.9f, 0.9f, .0f);

	// thực hiện việc chuyển đổi.
	
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

