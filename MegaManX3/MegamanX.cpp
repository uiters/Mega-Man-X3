#include "MegamanX.h"
#include "Brick.h"



void MegamanX::collisionStatic(unordered_map<int, CTreeObject*>* staticObjects)
{
	vector<CollisionEvent*> coEvents;
	vector<CollisionEvent*> coEventsResult;
	//x += dx;
	 collision->findCollisions(dt, this, *staticObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		debugOut(L" %f\n", speed.vy);
		//onAir = true;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		Collision::getInstance()->filterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.2f;
		y += min_ty * dy;// +ny * 0.2f;
		debugOut(L" %f ", speed.vy);
		if (nx != 0)
			speed.vx = 0;
		if (ny != 0)
			speed.vy = 0;
		debugOut(L" %f\n", speed.vy);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			auto e = coEventsResult[i];

			if (dynamic_cast<Brick *>(e->obj))
			{
				if (e->ny < 0)
				{
					speed.vy = 0;
					onAir = false;
					state = stand;
				}
				else if (e->nx != 0)
				{

				}
			}
		}
	}

	UINT size = coEvents.size();
	for (UINT i = 0; i < size; ++i) delete coEvents[i];
}

void MegamanX::collisionDynamic(unordered_map<int, CTreeObject*>* dynamicObjects)
{
	
}

MegamanX::MegamanX(UINT idTexture, float x, float y, float vx, float vy) :DynamicObject(idTexture, x, y, vx, vy)
{

}

MegamanX::~MegamanX()
{
}


void MegamanX::update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects)
{
	GameObject::update(dt);
	countTimeX.update();
	countTimeC.update();
	countTimeZ.update();
	debugOut(L"%f ", speed.vy);
	speed.vy += 0.005f * dt;
	debugOut(L" %f", speed.vy);
	collisionStatic(staticObjects);
	collisionDynamic(dynamicObjects);
}


void MegamanX::render(DWORD dt, D3DCOLOR colorBrush)
{

	if (countTimeX.isStop())
	{
		if (onAir)
		{
			countTimeX.start();
			(stack == DIK_Z) ? state = fall_shoot : state = fall;
		}
	}


	if (countTimeC.isStop() && countTimeX.isStop() && state != run)
	{
		state = stand;
	}


	if (!isKeyDown(DIK_Z) && !isKeyDown(DIK_X) && !isKeyDown(DIK_C) && !isKeyDown(DIK_LEFTARROW) && !isKeyDown(DIK_RIGHTARROW))
	{
		(onAir) ? state = fall : state = stand;
	}

	if (countTimeZ.isRunning()) state = shot;



	switch (state)
	{
	case stand:
	case shoot:
		speed.vx = 0;
		speed.vy = 0;
		break;
	case run:
	case run_shoot:
		(isFlipX) ? speed.vx = -0.1 : speed.vx = 0.1;
		(isKeyDown(DIK_X)) ? state = jump : state = run;
		(isKeyDown(DIK_X)) ? speed.vy = -0.15 : speed.vy = 0;
		break;
	case dash:
	case dash_shoot:
		(isFlipX) ? speed.vx = -0.15 : speed.vx = 0.15;
		speed.vy = 0;
		break;
	case jump:
		speed.vy = -0.15;
		(isKeyDown(DIK_LEFTARROW) || isKeyDown(DIK_RIGHTARROW)) ? ((isFlipX) ? speed.vx = -0.1 : speed.vx - 0.1) : speed.vx = 0;
		break;
	case fall:
	case fall_shoot:
		speed.vy = 0.15;
		(isKeyDown(DIK_LEFTARROW) || isKeyDown(DIK_RIGHTARROW)) ? ((isFlipX) ? speed.vx = -0.05 : speed.vx - 0.05) : speed.vx = 0;
		break;
	case shock:
		speed.vx = 0;
		speed.vy = 0;
		break;
	default:
		break;
	}

	//if (y >= 660)
	//{
	//	onAir = false;
	//	y = 660;
	//	//speed.vy = 0;
	//}

	auto center = cameraGlobal->transform(x, y);
	if (isFlipX)
		_animations[state]->renderFlipX(center.x, center.y, false, colorBrush);
	else
		_animations[state]->render(center.x, center.y, false, colorBrush);
}

void MegamanX::onKeyDown(int keyCode)
{
	switch (keyCode)
	{

	case DIK_LEFTARROW:
		isFlipX = true;
		break;
	case DIK_RIGHTARROW:
		isFlipX = false;
		break;
	case DIK_UPARROW:

		break;
	case DIK_DOWNARROW:

		break;
	case DIK_Z:
		stack = DIK_Z;
		break;
	case DIK_X:
		if (!onAir && !countTimeX.isRunning())
		{
			countTimeX.start();
			state = jump;
			onAir = true;
		}

		stack = DIK_X;
		break;
	case DIK_C:
		if (!onAir && !countTimeC.isRunning())
		{
			countTimeC.start();
			state = dash;
		}
		stack = DIK_C;
		break;
	default:
		break;
	}
}

void MegamanX::onKeyUp(int keyCode)
{
	switch (keyCode)
	{
	case DIK_LEFTARROW:

		break;
	case DIK_RIGHTARROW:

		break;
	case DIK_UPARROW:

		break;
	case DIK_DOWNARROW:

		break;
	case DIK_Z:

		countTimeZ.start();

		if (countTimeX.isRunning())
		{
			shot = jump_shoot;
		}
		else if (countTimeC.isRunning())
		{
			shot = dash_shoot;
		}
		else if (onAir)
		{
			shot = fall_shoot;
		}
		else if (isKeyDown(DIK_LEFTARROW) || isKeyDown(DIK_RIGHTARROW))
		{
			shot = run_shoot;
		}
		else shot = shoot;
		break;
	case DIK_X:
		if (onAir)
		{
			state = fall;
			speed.vy =- 0.15;
			countTimeX.stop();
		}
		break;
	case DIK_C:
		countTimeC.stop();
		break;
	default:
		break;
	}
}

void MegamanX::keyState(BYTE *_state)
{
	if (countTimeC.isRunning() && stack == DIK_C)
	{

		if ((isKeyDown(DIK_LEFTARROW) && !isFlipX) || (isKeyDown(DIK_RIGHTARROW) && isFlipX))
		{
			state = stand;
			countTimeC.stop();
		}
	}
	else if (isKeyDown(DIK_LEFTARROW) || isKeyDown(DIK_RIGHTARROW))
	{
		if (isKeyDown(DIK_X) && !countTimeX.isRunning())
		{
			state = jump;
			countTimeX.start();
			onAir = true;
		}
		else if (!onAir)
		{
			if (countTimeZ.isRunning()) shot = run_shoot;
			else state = run;
		}
		/*else
		{
			if (countTimeZ.isRunning()) shot = fall_shoot;
			else state = fall;
		}*/
	}
}

