#include "Sprites.h"
#include "Game.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::getInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::draw(float x, float y, D3DCOLOR colorBrush)
{
	::draw(x, y, texture, left, top, right, bottom, colorBrush);
}

void CSprites::add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::get(int id)
{
	return sprites[id];
}



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
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}

	frames[currentFrame]->getSprite()->draw(x, y, colorBrush);
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