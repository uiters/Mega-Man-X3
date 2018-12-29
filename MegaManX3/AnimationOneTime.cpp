#include "AnimationOneTime.h"



void AnimationOneTime::_updateFrame()
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	if (isDone) return;
	else
	{
		DWORD t = frames[currentFrame]->getTime();
		if (now - lastFrameTime > t)
		{
			++currentFrame;

			lastFrameTime = now;
			if (currentFrame == frames.size()) 
				isDone = true, --currentFrame;
		}
	}
}

AnimationOneTime::AnimationOneTime(int defaultTime) : CAnimation(defaultTime)
{
	isDone = false;
}

void AnimationOneTime::render(float x, float y, bool center, D3DCOLOR colorBrush)
{
	if (!isDone)
		_updateFrame(),
		frames[currentFrame]->getSprite()->draw(x, y, center, colorBrush);
}

void AnimationOneTime::renderFlipX(float x, float y, bool center, D3DCOLOR colorBrush)
{
	if (!isDone)
		_updateFrame(),
		frames[currentFrame]->getSprite()->drawFlipX(x, y, center, colorBrush);
}

void AnimationOneTime::renderFlipY(float x, float y, bool center, D3DCOLOR colorBrush)
{
	if (!isDone)
		_updateFrame(),
		frames[currentFrame]->getSprite()->drawFlipY(x, y, center, colorBrush);
}

bool AnimationOneTime::isFinish()
{
	return isDone;
}

bool AnimationOneTime::isLastFrame()
{
	return isDone;
}

void AnimationOneTime::reset()
{

	isDone = false;
	currentFrame = -1;
}


AnimationOneTime::~AnimationOneTime()
{
}
