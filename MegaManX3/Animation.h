#ifndef _Animation_H
#define _Animation_H
 
#include "Sprites.h"

/*
	Sprite animation
*/
class CAnimationFrame;
class CAnimation;

typedef CAnimationFrame *LPANIMATION_FRAME;
typedef CAnimation *LPANIMATION;

class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }

	DWORD getTime() { return time; }
	LPSPRITE getSprite() { return sprite; }
};


class CAnimation : public Graphics::Render
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void add(int spriteId, DWORD time = 0);
	void render(float x, float y, D3DCOLOR colorBrush = WHITE(255)) override;
	void renderFlip(int x, int y, bool isLeft, float width, float height, D3DCOLOR colorBrush = WHITE(255)) override;
	void reset();//reset frame
};


class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void add(int id, LPANIMATION ani);
	LPANIMATION get(int id);

	static CAnimations * getInstance();
};

#endif // !_Animation_H