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
class CTreeObject;
class CTextures;

struct CollisionEvent;
class Collision;
class GameObject
{
protected:
	UINT _id = 0;
	UINT _idObject = 0;//type name
	
	bool _canReset = true;
	bool _canRemove = false;

	LPDIRECT3DTEXTURE9 _texture;

	static unordered_map<UINT, LPANIMATION> _animations;
	static Collision * collision;
public:
	float x = 0, y = 0;
	float dx = 0; // dx = vx * dt
	float dy = 0; // dy = vy * dt

	bool visible = true;
	bool canAttack = false;
	UINT state = 0;
	Speed speed;
	DWORD dt = 0;
	CTreeObject* currentNode = 0;

public:
	GameObject(UINT idTexture, int x = 0, int y = 0, float vx = 0, float vy = 0);
	GameObject(UINT id, UINT idTexture, int x = 0, int y = 0, float vx = 0, float vy = 0);

	GameObject() {}
	~GameObject();
	void addAnimation(UINT animationId);
	bool canReset();
	bool canRemove();

	LPDIRECT3DTEXTURE9 getTexture() { return _texture; }
	UINT getID() { return _id; }
	UINT getIDObject() { return _idObject; }
public:
	
	virtual void getBoundingBox(float & left, float & top, float & right, float & bottom) = 0;
	virtual CRectangle* getBoundingBox();
	virtual void update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects = 0, unordered_map<int, CTreeObject*>* dynamicObjects = 0);
	virtual void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) {}
	virtual void reset() {}
	virtual void remove() {}
	virtual void loadResources() = 0;
};

#endif //! _GameObject_H