#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "Game.h"
#include "ConstColor.h"
#include "Sprite.h"
#include "ConstStruct.h"
class GameObject
{
protected:
	int state;
	float x, y, width, height;
	Speed speed;
	LPDIRECT3DTEXTURE9 texture;
public:
	LPDIRECT3DTEXTURE9 getTexture() { return texture; }

	void setPosition(float x, float y) { this->x = x; this->y = y; }

	GameObject(LPCWSTR path, float x = 0, float y = 0, float width = 0, float height = 0);

	Speed getSpeed() { return speed; }
	void getSpeed(float &vx, float &vy) { vx = speed.vx, vy = speed.vy; }

	virtual void getBound(float &left, float &top, float &right, float &bottom) { left = x, top = y, right = x + width, bottom = y + height; }
	virtual Rect getBound() { 
		Rect rect; 
		rect.left = x;
		rect.top = y;
		rect.right = x + width;
		rect.bottom = y + height;
		return rect;

	}

	virtual void setState() {}

	virtual void Update(DWORD dt) {}
	virtual void Render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) { Game::GetInstance()->Draw(x, y, texture, colorBrush); }

	~GameObject();
};

