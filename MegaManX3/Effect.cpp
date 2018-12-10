#include "Effect.h"

Effect::Effect()
{
	
}

Effect::~Effect()
{
}

void Effect::createEffect(float x, float y)
{
	AnimationPoint e = { PointF(x, y) , *animation };
	animations.emplace_back(e);
	infity = false;
}

void Effect::createEffectInfinity(float x, float y)
{

}

void Effect::render(DWORD dt, bool center,  D3DCOLOR colorBrush)
{
	for (auto it = animations.begin(); it != animations.end(); )
	{
		auto ani = &(*it).animation;
		auto pos = cameraGlobal->transform((*it).point.x, (*it).point.y);
		ani->render(pos.x, pos.y, center, colorBrush);

		if (ani->isFinish())
		{
			it = animations.erase(it);
		}
		else ++it;
	}
}

void Effect::stop()
{
	animations.clear();
}
