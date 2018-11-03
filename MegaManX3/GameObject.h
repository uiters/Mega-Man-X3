#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "Game.h"
#include "Sprites.h"
#include "QuadTree.h"
#include "Textures.h"

class QuadTree;
class CTextures;


class GameObject
{
protected:
	int _id;
	UINT width, height;
	LPDIRECT3DTEXTURE9 texture;

public:
	float x, y;
	GameObject(UINT idTexture, float x = 0, float y = 0, UINT width = 0, UINT height = 0);
	QuadTree* currentNode;
	LPDIRECT3DTEXTURE9 GetTexture() { return texture; }
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void getSize(float &width, float &height);

	virtual void Update(DWORD dt) {}
	virtual void Render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) { Game::GetInstance()->Draw(x, y, texture, colorBrush); }
	virtual RECT getBound();
	~GameObject();
};

