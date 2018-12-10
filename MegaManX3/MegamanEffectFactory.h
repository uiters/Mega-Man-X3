#ifndef _MegamanEffectFactory_H_
#define _MegamanEffectFactory_H_
#include "DashSmoke.h"
#include "DashSpark.h"
#include "WallKick.h"
#include "WallSlide.h"
class MegamanEffectFactory
{
private:
	DashSmoke* dashSmoke = null;
	DashSpark* dashSpark = null;
	WallKick* wallKick = null;
	WallSlide* wallSlide = null;

public:
	MegamanEffectFactory();
	~MegamanEffectFactory();

	void createDashSmoke(float x, float y);
	void createDashSpark(float x, float y);
	void createWallKick(float x, float y);
	void createWallSlide(float x, float y);

	void stopDashSpark();
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
};

#endif // !_MegamanEffectFactory_H_
