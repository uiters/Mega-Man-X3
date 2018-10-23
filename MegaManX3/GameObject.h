#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "Game.h"
#include "ConstColor.h"
#include "Sprite.h"
#include "QuadTree.h"

class QuadTree;


class GameObject
{
protected:
	int _id;
	float x, y;
	UINT width, height;
	LPDIRECT3DTEXTURE9 texture;
	RECT rect;
	static int _counter;

public:
	RECT getRect() {
		return rect;
	}
	QuadTree* currentNode;
	LPDIRECT3DTEXTURE9 GetTexture() { return texture; }
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	GameObject(LPCWSTR path, float x = 0, float y = 0, UINT width = 0, UINT height = 0);
	virtual void Update(DWORD dt) {
	}
	virtual void Render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) { Game::GetInstance()->Draw(x, y, texture, colorBrush); }

	bool operator ==(const GameObject &b) const {
		return  this->_id == b._id;
	}

	~GameObject();
};

