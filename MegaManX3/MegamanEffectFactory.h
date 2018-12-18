#ifndef _MegamanEffectFactory_H_
#define _MegamanEffectFactory_H_
#include "DashSmoke.h"
#include "DashSpark.h"
#include "WallKick.h"
#include "WallSlide.h"
#include "ChargedEffect.h"
class MegamanEffectFactory
{
private:
	DashSmoke*		dashSmoke	= null;
	DashSpark*		dashSpark	= null;
	WallKick*		wallKick	= null;
	WallSlide*		wallSlide	= null;
	ChargedEffect*	charged		= null;

	bool isCharge = false;
public:
	MegamanEffectFactory();
	~MegamanEffectFactory();

	void createDashSmoke(float x, float y);
	void createDashSpark(float x, float y, bool isLeft);
	void createWallKick(float x, float y);
	void createWallSlide(float x, float y);
	void createShoot(int level);

	void stopDashSpark();
	void stopShoot();
	void render(DWORD dt,float x, float y, int width, int height, D3DCOLOR colorBrush = WHITE(255));
};

#endif // !_MegamanEffectFactory_H_
