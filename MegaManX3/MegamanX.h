#ifndef _MegamanX_H
#define _MegamanX_H
#pragma once
#include "DynamicObject.h"
#include "GameObject.h"
#include "CTime.h"
#include "CKey.h"
#include "Camera.h"
#include "CollisionEvent.h"
#include "KeyController.h"
#include "Brick.h"
#include "MegamanEffectFactory.h"
#include "MegamanWeapon.h"
#include "ConstGlobals.h"
class KeyController;
class MegamanX :
	public DynamicObject,
	public CKey
{
private:
	void collisionStatic(unordered_map<int, CTreeObject*>* staticObjects);
	void collisionDynamic(unordered_map<int, CTreeObject*>* dynamicObjects);

	void setHurt();

	KeyController* keyController;
	MegamanX* clone(int id, int x, int y) override;
	MegamanEffectFactory* effect;
	MegamanWeapon *weapon;
	MegamanX() {}
private:

	CTime countDissapear = (800);
	CTime timePreDie = (500);
	PointF p1 = { 400, 290 };
	PointF p2 = { 410, 300 };
	PointF p3 = { 400, 310 };
	PointF p4 = { 390, 300 };
	PointF p5 = { 410, 290 };
	PointF p6 = { 410, 310 };
	PointF p7 = { 390, 310 };
	PointF p8 = { 390, 290 };
public:
	MegamanX(UINT idTexture, float x = 0, float y = 0, float vx = 0, float vy = 0);
	~MegamanX();

	bool isFlipX = false; //lật hình (mặc định hướng về phải)
	int  onWall = 0; //đang ở trên tường -1 left - 1 right
	bool onAir = false; //đang ở trên không trung
	bool hurt() { return isHurt; }
private:
	bool isHurt = false;
	bool isProtect = false;
	CTime timeHurt = (500); //animation hurt
	CTime timeProtect = (3000); //animation flicker;
	bool showblur = false; //for blur draw
	int delay = 3;

	int width, height;
	void loadResources() override {}
	void dissapear(DWORD dt, D3DCOLOR colorBrush);
	void resetPoint();
	void config(Point& center);
public:
	void update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects) override;
	void updateState(DWORD dt);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	void onKeyDown(int) override;
	void onKeyUp(int) override;
	void keyState(BYTE*) override;
	void getBoundingBox(float& left, float& top, float& right, float &bottom) override;

private:
	void dynamicCollisionThis(unordered_map<int, CTreeObject*>* dynamicObjects);
	void bulletCollisionDynamic(unordered_map<int, CTreeObject*>* dynamicObjects);

	bool collisionGameObject(GameObject* obj1, GameObject* obj2);
	bool collisionBullet(DynamicObject* obj1, Weapon* bullet1, GameObject* obj2);
	
};
#endif // !_MegamanX_H