#ifndef _AnimationOneTime_h_
#define _AnimationOneTime_h_

#include "Animation.h"
class AnimationOneTime :
	public CAnimation
{
protected:
	void _updateFrame() override;
	bool isDone = false;
public:
	AnimationOneTime(int defaultTime);
	void render(float x, float y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) override;
	void renderFlipX(float x, float y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) override;
	void renderFlipY(float x, float y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) override;
	bool isFinish();
	~AnimationOneTime();
};
#endif // !_AnimationOneTime_h_
