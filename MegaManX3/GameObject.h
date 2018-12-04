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
class CTreeObject;
class CTextures;

class GameObject
{
protected:
	UINT _id = 0;
	
	CRectangle box;
	bool _canReset = true;
	bool _canRemove = false;

	
	LPDIRECT3DTEXTURE9 _texture;

	static unordered_map<UINT, LPANIMATION> _animations;
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
	ObjectType type;

public:
	GameObject(UINT idTexture, int x = 0, int y = 0, float vx = 0, float vy = 0);
	GameObject() {}
	~GameObject();


	void addAnimation(UINT animationId);
	//void renderBoundingBox(); // for test

	void getSize(int &width, int &height);
	bool canReset();
	bool canRemove();

	ObjectType getType();	
	LPDIRECT3DTEXTURE9 getTexture();

public:
	void getBoundingBox(int & left, int & top, int & right, int & bottom);
	virtual CRectangle* getBoundingBox();
	virtual void updateBox();
	virtual void update(DWORD dt, vector<LPObject> *coObjects = 0);
	virtual void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) {}
	virtual void reset() {}
	virtual void remove() {}
	virtual void loadResource() {}
};

#endif //! _GameObject_H