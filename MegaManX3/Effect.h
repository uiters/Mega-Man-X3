#pragma once
#include <vector>
#include "AnimationOneTime.h"
#include "ConstGlobals.h"
#include "Camera.h"

using namespace std;

struct AnimationPoint
{
	PointF point;
	AnimationOneTime animation;
};

class Effect
{
protected:
	vector<AnimationPoint> animations;//list animation point

	bool infity = false;
	AnimationOneTime* animation;
	virtual void loadResources() = 0;

public:

	Effect();
	~Effect();

	virtual void createEffect(float x, float y);//create effect one time at point x, y 
	virtual void createEffectInfinity(float x, float y);
	virtual void render(DWORD dt, bool center,  D3DCOLOR colorBrush = WHITE(255));
	virtual void stop();
};

