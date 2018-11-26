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

void CAnimation::add(UINT spriteId, DWORD time)
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
	frames[currentFrame]->getSprite()->draw(x, y, center, colorBrush);
}

void CAnimation::renderFlipX(int x, int y, bool center, D3DCOLOR colorBrush)
{
	_updateFrame();
	frames[currentFrame]->getSprite()->drawFlipX(x, y, center, colorBrush);
}

void CAnimation::renderFlipY(int x, int y, bool center, D3DCOLOR colorBrush)
{
	_updateFrame();
	frames[currentFrame]->getSprite()->drawFlipY(x, y, center, colorBrush);
}


void CAnimation::reset()
{
	currentFrame = -1;
}

Size CAnimation::getSize()
{
	return frames[currentFrame]->getSprite()->getSize();
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::getInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::add(UINT id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::get(UINT id)
{
	return animations[id];
}
