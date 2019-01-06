#ifndef __GameObject_H__
#define __GameObject_H__
#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Textures.h"
#include "Graphics.h"
#include "Debugs.h"
#include "Animation.h"
#include "CollisionEvent.h"
#include "CSounds.h"
class GameObject;
class CTextures;

struct CollisionEvent;
class Collision;
class GameObject
{
protected:
	UINT _id = 0;
	unordered_map<UINT, LPANIMATION> _animations;
	static Collision * collision;
public:
	bool toLeft = false;
	float x = 0, y = 0;
	float dx = 0; // dx = vx * dt
	float dy = 0; // dy = vy * dt

	bool visible = true;
	UINT state = 0;
	Speed speed;
	DWORD dt = 0;
public:
	GameObject(UINT id, float x = 0, float y = 0, float vx = 0, float vy = 0);

	GameObject() {}
	
	~GameObject();

public:
	void addAnimation(UINT animationId);
	UINT getID() { return _id; }

public:
	virtual void getBoundingBox(float & left, float & top, float & right, float & bottom) = 0;
	virtual CRectangle getBoundBox();
	virtual void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0);
	virtual void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) {}
	virtual void reset() {}
	virtual void loadResources() = 0;
	virtual void setReset() {}

public:
	bool collisionBullet(GameObject * bullet1, GameObject * obj2);
	bool collisionGameObject(GameObject * obj1, GameObject * obj2);

};

#endif //! _GameObject_H