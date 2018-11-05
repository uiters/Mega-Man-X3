#ifndef __GameObject_H__
#define __GameObject_H__
#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>


#include "Sprites.h"
#include "QuadTree.h"
#include "Textures.h"
#include "Graphics.h"
#include "Debugs.h"
#include "Animation.h"
class QuadTree;
class CTextures;

class GameObject
{
protected:
	UINT _id = 0;
	UINT _state = 0;
	long _width = -1;
	long _height = -1;
	bool _canReset = true;
	bool _canRemove = false;

	vector<LPANIMATION> _animations;
	LPDIRECT3DTEXTURE9 _texture;


public:
	float x = 0, y = 0;
	float dx = 0; // dx = vx * dt
	float dy = 0; // dy = vy * dt
	bool visible = true;
	bool canAttack = false;

	Speed speed;
	DWORD dt = 0;
	QuadTree* currentNode = 0;
	ObjectType type;

public:
	GameObject(UINT idTexture, float x = 0, float y = 0, float vx = 0, float vy = 0);
	GameObject() {}
	~GameObject();


	void addAnimation(UINT animationId);
	void renderBoundingBox(); // for test

	void setState(UINT state);
	void getSize(float &width, float &height);
	int	 getState();
	bool canReset();
	bool canRemove();

	ObjectType getType();
	LPDIRECT3DTEXTURE9 getTexture();

public:
	virtual void getBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual RECT getBoundingBox();
	virtual void update(DWORD dt, vector<LPObject> *coObjects = 0);
	virtual void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) {}
	virtual void reset() {}
	virtual void remove() {}
};

#endif //! _GameObject_H