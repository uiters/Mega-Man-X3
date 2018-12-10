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
	void render(int x, int y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) override;
	void renderFlipX(int x, int y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) override;
	void renderFlipY(int x, int y, bool center = false, D3DCOLOR colorBrush = WHITE(255)) override;
	bool isFinish();
	~AnimationOneTime();
};
#endif // !_AnimationOneTime_h_
