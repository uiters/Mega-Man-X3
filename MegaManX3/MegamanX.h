#ifndef _MegamanX_H_
#define _MegamanX_H_
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
#include "HPBar.h"
class KeyController;
class MegamanX :
	public DynamicObject,
	public CKey
{
private:
	void collisionStatic(unordered_map<int, GameObject*>* staticObjects);
	void collisionDynamic(unordered_map<int, GameObject*>* dynamicObjects);

	

	KeyController* keyController;
	MegamanEffectFactory* effect;
	MegamanWeapon *weapon;

private:
	Elevator* elevator = null;
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
	MegamanX(UINT id, float x = 0, float y = 0, float vx = 0, float vy = 0);
	~MegamanX();

	bool isFlipX = false; //lật hình (mặc định hướng về phải)
	int  onWall = 0; //đang ở trên tường -1 left - 1 right
	bool onAir = false; //đang ở trên không trung
	bool hurt() { return isHurt; }
	void setHurt();
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
	bool protect() { return isProtect; }
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects) override;
	void updateStage(DWORD dt, unordered_map<int, GameObject*>*dynamicObjects);

	void updateState(DWORD dt);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	void onKeyDown(int) override;
	void onKeyUp(int) override;
	void keyState(BYTE*) override;
	void getBoundingBox(float& left, float& top, float& right, float &bottom) override;
	void setFloor(StaticObject* obj) { keyController->setFloor(obj); }
	void receiveDamage(float damage) override;
private:
	void dynamicCollisionThis(unordered_map<int, GameObject*>* dynamicObjects);
	void bulletCollisionDynamic(unordered_map<int, GameObject*>* dynamicObjects);
};
#endif // !_MegamanX_H_