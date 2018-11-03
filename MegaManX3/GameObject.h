#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "Game.h"
#include "Sprites.h"
#include "QuadTree.h"
#include "Textures.h"
#include "Graphics.h"

class QuadTree;
class CTextures;

class GameObject
{
protected:
	UINT _id;
	float width, height;
	LPDIRECT3DTEXTURE9 texture;
	int state;
	vector<LPANIMATION> animations;

public:
	float x, y;
	float dx; // dx = vx * dt
	float dy; // dy = vy * dt
	Speed speed;
	DWORD dt;
	QuadTree* currentNode;

public:
	GameObject(UINT idTexture, float x = 0, float y = 0, float vx = 0, float vy = 0, float width = 0, float height = 0);

	// get
	LPDIRECT3DTEXTURE9 getTexture() { return texture; }
	void getSize(float &width, float &height);
	int getState() { return state; }

	void addAnimation(UINT animationId);

	void renderBoundingBox(); // for test


	virtual void getBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual RECT getBoundingBox();
	virtual void setState(UINT state) { this->state = state; }
	virtual void update(DWORD dt, vector<LPObject> *coObjects = 0);
	virtual void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) {}
	~GameObject();
};

