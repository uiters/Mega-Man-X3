#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "Game.h"
#include "ConstColor.h"
#include "Sprite.h"
class GameObject
{
protected:
	float x, y;
	float width, height;
	LPDIRECT3DTEXTURE9 texture;
public:
	LPDIRECT3DTEXTURE9 GetTexture() { return texture; }
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	GameObject(LPCWSTR path, float x = 0, float y = 0, float width = 0, float height = 0);
	virtual void Update(DWORD dt) {}
	virtual void Render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) { Game::GetInstance()->Draw(x, y, texture, colorBrush); }
	~GameObject();
};

