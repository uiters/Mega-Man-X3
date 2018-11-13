#include "Animation.h"

void CAnimation::_updateFrame()
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
}

void CAnimation::add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::getInstance()->get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::render(int x, int y, bool center, D3DCOLOR colorBrush)
{
	_updateFrame();
	if (center)
		frames[currentFrame]->getSprite()->drawCenter(x, y, colorBrush);
	else frames[currentFrame]->getSprite()->draw(x, y, colorBrush);
}

void CAnimation::renderFlip(int x, int y, bool isX, bool center, D3DCOLOR colorBrush)
{
	_updateFrame();
	if (center)
		frames[currentFrame]->getSprite()->drawFlipCenter(x, y, isX, colorBrush);
	else frames[currentFrame]->getSprite()->drawFlip(x, y, isX, colorBrush);
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
