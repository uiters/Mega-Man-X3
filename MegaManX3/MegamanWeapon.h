#ifndef _MegamanWeapon_H_
#define _MegamanWeapon_H_
#include "BusterShot.h"
#include "ChargedShot1.h"
#include "ChargedShot2.h"
class MegamanWeapon
{
private:
	vector<Weapon*>* weapons;
public:
	void update(DWORD dt);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void createWeapon(float x, float y, int level,bool isLeft);
	MegamanWeapon(vector<Weapon*>* weapons);
	~MegamanWeapon();
};

#endif // !_MegamanWeapon_H_