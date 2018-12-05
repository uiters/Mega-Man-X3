#ifndef _MegamanX_H

#define _MegamanX_H
#include "DynamicObject.h"
#include "GameObject.h"
#include "CTime.h"
#include "CKey.h"
#include "Camera.h"
#include "CollisionEvent.h"
class MegamanX :
	public DynamicObject,
	public CKey
{
private:
	void collisionStatic(unordered_map<int, CTreeObject*>* staticObjects);
	void collisionDynamic(unordered_map<int, CTreeObject*>* dynamicObjects);
public:
	MegamanX(UINT idTexture, float x = 0, float y = 0, float vx = 0, float vy = 0);
	~MegamanX();

	bool isFlipX = false; //lật hình (mặc định hướng về phải)
	bool onWall = false; //đang ở trên tường
	bool onAir = false; //đang ở trên không trung

	int stack;
	CTime countTimeX = CTime(600);
	CTime countTimeC = CTime(800);
	CTime countTimeZ = CTime(150);
	int shot;
public:

	void update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	void onKeyDown(int) override;
	void onKeyUp(int) override;
	void keyState(BYTE*) override;

};
#endif // !_MegamanX_H