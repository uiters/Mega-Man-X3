#ifndef _Animation_H_
#define _Animation_H_

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
protected:
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
	virtual void _updateFrame();
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void add(UINT spriteId, DWORD time = 0);

	bool isLastFrame();//warring

	//center is draw center
	virtual void render(float x, float y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) override;
	virtual void renderFlipX(float x, float y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) override;
	virtual void renderFlipY(float x, float y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) override;
	virtual void reset();//reset frame
	Size getSize();
};


class CAnimations
{
	static CAnimations * __instance;

	unordered_map<UINT, LPANIMATION> animations;

public:
	void add(UINT id, LPANIMATION ani);
	LPANIMATION get(UINT id);
	bool isLastFrame(UINT id);

	static CAnimations * getInstance();
};

#endif // !_Animation_H_