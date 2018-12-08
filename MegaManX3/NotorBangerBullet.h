#pragma once
#include <stdlib.h>
#include "Weapon.h"

#define NOTOR_BANGER_BULLET_GRAVITY 0.01f
#define NOTOR_BANGER_BULLET_SPEED_X_SMALL 0.015f
#define NOTOR_BANGER_BULLET_SPEED_Y_SMALL 0.2f
#define NOTOR_BANGER_BULLET_SPEED_X_MEDIUM 0.08f
#define NOTOR_BANGER_BULLET_SPEED_Y_MEDIUM 0.2f
#define NOTOR_BANGER_BULLET_SPEED_X_LARGE 0.16f
#define NOTOR_BANGER_BULLET_SPEED_Y_LARGE 0.2f

#define NOTOR_BANGER_BULLET_STATE_DEFAULT 0
// Tao 2 state, 1 huong len, 1 huong xuong

#define NOTOR_BANGER_BULLET_ID_TEXTURE 801

class NotorBangerBullet : public Weapon
{
public:
	NotorBangerBullet();
	NotorBangerBullet(float x, float y, bool nx, bool ny, int distance);
	NotorBangerBullet(int id, float x, float y, bool nx, bool ny, int distance);
	~NotorBangerBullet();
	void update(DWORD dt, vector<LPObject> *coObjects = 0);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void setState(int state);
	void loadResources();
	void setPosition(float x, float y);
	bool isDelete;
	bool nx;
	bool ny;
private:
	float limit;
	int distance;
};

