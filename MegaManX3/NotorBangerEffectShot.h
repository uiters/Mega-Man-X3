#pragma once
#include "Camera.h"
#include "ConstGlobals.h"
#include "StaticObject.h"

#define NOTOR_BANGER_EFFECT_SHOT_STATE_DEFAULT 0

#define NOTOR_BANGER_EFFECT_SHOT_ID_TEXTURE 9011


class NotorBangerEffectShot : public StaticObject
{
public:
	NotorBangerEffectShot(float x, float y);
	~NotorBangerEffectShot();
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void loadResources();
	void setState(int state);
};

