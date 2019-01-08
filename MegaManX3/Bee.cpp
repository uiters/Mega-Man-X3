#include "Bee.h"


void Bee::loadResources()
{
	this->addAnimation(Hornet_Bee_Type_1);
	this->addAnimation(Hornet_Bee_Type_2);
	this->addAnimation(Hornet_Bee_Die_1);
	this->addAnimation(Hornet_Bee_Die_2);
	state = Hornet_Bee_Type_1;
}

Bee::Bee(float x, float y, float vx, float vy, bool toLeft, bool isChase)
{
	
	loadResources();
	this->x = x;
	this->y = y;
	speed.vx = vx;
	speed.vy = vy;
	this->toLeft = toLeft;

	timeSwitchState.setTimeUp(rand() % 5000 + 1000); //[1, 6]s

	timeDie.start();
	timeSwitchStateDie.start();
	timeSwitchState.start();
	if (isChase)
	{
		mech = &Bee::chase;
		_damage = 4.0f;
	}
	else
	{
		mech = &Bee::fly;
		_damage = 2.0f;
	}

}


Bee::~Bee()
{
	if(_isCollision)
		_weaponEffect->createBeeEffect(x + 11, y + 11);
}

void Bee::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 22;
	bottom = y + 25;
}

void Bee::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	if (visible)
	{
		timeDie.update();

		if (timeDie.isStop())
		{
			visible = false;
			_weaponEffect->createBeeEffect(x + 11, y + 11); // explosion
			return;
		}

		timeSwitchStateDie.update();
		timeSwitchState.update();

		if (timeSwitchState.isStop())
			switchState();

		if (!isSwitchDie && timeSwitchStateDie.isStop())
			isSwitchDie = true,
			state = Hornet_Bee_Die_1;



		this->staticObjects = staticObjects;
		GameObject::update(dt);
		(this->*mech)();
		
	}
}

void Bee::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (visible)
	{
		auto pos = &cameraGlobal->transform(x, y);
		if (toLeft)
			_animations[state]->render(pos->x, pos->y);
		else _animations[state]->renderFlipX(pos->x, pos->y);
	}
}


//mech
void Bee::chase()
{
	setDirection();
	y += dy;
	x += dx;

	float distanceX = mainGlobal->x - x;
	float distanceY = mainGlobal->y - y;

	//if(distanceX / 5.f < )

	speed.vy = distanceY / 1000.f; //calculate speed
	speed.vx = distanceX / 1000.f;
}

void Bee::fly()
{
	collisionStatic();
	//speed.vx += speed.vx  > 0 ? -0.0001f *dt : 0.0001f *dt;
	//speed.vy += speed.vy > 0 ? -0.0001f *dt : 0.0001f *dt;
}

void Bee::stand()
{

}

void Bee::switchState()
{
	if (state == Hornet_Bee_Type_1 || state == Hornet_Bee_Die_1)
	{
		state += 2;
	}
	else state -= 2;
}

void Bee::collisionStatic()
{
	vector<CollisionEvent*> coEvents;
	vector<CollisionEvent*> coEventsResult;

	collision->findCollisions(dt, this, *staticObjects, coEvents);
	UINT size = coEvents.size();

	if (size == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		collision->filterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		mech = &Bee::stand;
	}
	for (UINT i = 0; i < size; ++i) delete coEvents[i];
}

void Bee::setDirection()
{
	if (x + 11 / 2 > mainGlobal->x)
		toLeft = true;
	else
		toLeft = false;
}