#include "DashSmoke.h"


DashSmoke::DashSmoke(UINT idAnimation) : Effect(idAnimation)
{

}



void DashSmoke::createEffect(int x, int y)
{
	AnimationPoint e = { Point(x, y) , *animation };
	animations.emplace_back(e);
	infity = false;
}

void DashSmoke::render(DWORD dt, D3DCOLOR colorBrush)
{
	for (auto it = animations.begin(); it != animations.end(); ++it) 
	{
		auto center = &cameraGlobal->transform((*it).point.x, (*it).point.y);
		(*it).animation.render(center->x, center->y, colorBrush);
		if ((*it).animation.isLastFrame())
			animations.erase(it);
	}
	

}

DashSmoke::~DashSmoke()
{

}
