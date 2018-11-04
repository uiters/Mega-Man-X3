#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>


#include "Game.h"
#include "Sprites.h"
#include "QuadTree.h"
#include "Textures.h"
#include "Graphics.h"
#include "Debugs.h"

class QuadTree;
class CTextures;

class GameObject
{
protected:
	UINT _id;
	int _state;
	long _width, _height;
	bool _canReset;
	bool _canRemove;
	bool _canDamage;

	vector<LPANIMATION> _animations;
	LPDIRECT3DTEXTURE9 _texture;


public:
	float x, y;
	float dx; // dx = vx * dt
	float dy; // dy = vy * dt
	bool visible;

	Speed speed;
	DWORD dt;
	QuadTree* currentNode;
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
	bool canDamage();

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

