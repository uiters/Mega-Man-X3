#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include"ConstColor.h"
#include "Graphics.h"
using namespace std;

class CSprite;
class CSprites;

typedef CSprite * LPSPRITE;

class CSprite : public Graphics::Draw
{
private:
	int id;				// Sprite ID in the sprite database
	int left; 
	int top;
	int right;
	int bottom;
	LPDIRECT3DTEXTURE9 texture;

public: 
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texure);

	void draw(float x, float y, D3DCOLOR colorBrush = WHITE(255)) override;
	void drawFlip(int x, int y, bool isLeft, float width, float height, D3DCOLOR colorBrush = WHITE(255)) override;
};

/*
	Manage sprite database
*/
class CSprites
{
private:
	static CSprites * __instance;
	unordered_map<int, LPSPRITE> sprites;

public:
	void add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture);
	LPSPRITE get(int id);
	void deleteAt(int id);
	void clear();
public:
	static CSprites * getInstance();
};



