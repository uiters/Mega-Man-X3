#ifndef _MegamanX_H
#define _MegamanX_H

#include "DynamicObject.h"
#include "GameObject.h"
#include "CTime.h"
#include "CKey.h"
#include "Camera.h"
#include "CollisionEvent.h"
#include "KeyController.h"
#include "Brick.h"
#include "MegamanEffectFactory.h"
class KeyController;
class MegamanX :
	public DynamicObject,
	public CKey
{
private:
	void collisionStatic(unordered_map<int, CTreeObject*>* staticObjects);
	void collisionDynamic(unordered_map<int, CTreeObject*>* dynamicObjects);

	KeyController* keyController;
	MegamanX* clone(int id, int x, int y) override;
	MegamanEffectFactory* effect;

	MegamanX() {}
public:
	MegamanX(UINT idTexture, float x = 0, float y = 0, float vx = 0, float vy = 0);
	~MegamanX();

	bool isFlipX = false; //lật hình (mặc định hướng về phải)
	int  onWall = 0; //đang ở trên tường -1 left - 1 right
	bool onAir = false; //đang ở trên không trung
private:
	int width, height;
	int shot;
	void loadResources() override {}
public:
	void update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects) override;
	void updateState(DWORD dt);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	void onKeyDown(int) override;
	void onKeyUp(int) override;
	void keyState(BYTE*) override;
	void getBoundingBox(float& left, float& top, float& right, float &bottom) override;
	
};
#endif // !_MegamanX_H