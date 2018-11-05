#include "Animation.h"

void CAnimation::add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::getInstance()->get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::render(float x, float y, D3DCOLOR colorBrush)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->getTime();
		if (now - lastFrameTime > t)
		{
			++currentFrame;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}

	frames[currentFrame]->getSprite()->draw(x, y, colorBrush);
}

void CAnimation::renderFlip(int x, int y, bool isLeft, float width, float height, D3DCOLOR colorBrush)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->getTime();
		if (now - lastFrameTime > t)
		{
			++currentFrame;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
	}

	frames[currentFrame]->getSprite()->drawFlip(x, y, isLeft, width, height, colorBrush);
}

void CAnimation::reset()
{
	currentFrame = -1;
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::getInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::get(int id)
{
	return animations[id];
}