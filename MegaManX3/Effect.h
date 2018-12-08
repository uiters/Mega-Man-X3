#pragma once
#include "GameObject.h"
#include <vector>
#include "ConstGlobals.h"
#include "Animation.h"
using namespace std;

struct AnimationPoint
{
	Point point;
	CAnimation animation;
};

class Effect :
	public GameObject
{
private: 
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override {};
protected:
	vector<AnimationPoint> animations;//list animation point

	bool infity = false;
	LPANIMATION animation;
	
public:
	Effect(UINT idAnimation);
	~Effect();

	virtual void createEffect(int x, int y) = 0;//create effect one time at point x, y 
	virtual void createEffectInfinity(int x, int y) = 0;
	virtual void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) = 0;
};

