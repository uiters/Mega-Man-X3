#ifndef _ChargedEffect_H_
#define _ChargedEffect_H_

#include "Effect.h"
class ChargedEffect :
	public Effect
{
private:
	void loadResources() override;
	static ChargedEffect* _instance;
	ChargedEffect();
	void createEffect(float x, float y) override;
	void render(DWORD dt, bool center, D3DCOLOR colorBrush = WHITE(255)) override {}
	TextureID anis[2] = { TCharged1 , TCharged2 };
	CAnimation* ani;
public:
	static ChargedEffect* getInstance();
	void createCharged(int level);
	void render(int x, int y, bool center, D3DCOLOR colorBrush = WHITE(255));
	void stop() override;
	~ChargedEffect();
};

#endif // !_ChargedEffect_H_