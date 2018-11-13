#ifndef _Sprites_H_
#define _Sprites_H_

#pragma once

#include "Graphics.h"
#include "Textures.h"

using namespace std;

class CSprite;
class CSprites;

typedef CSprite * LPSPRITE;

class CSprite : public Graphics::Draw
{
protected:
	int id;				// Sprite ID in the sprite database
	CRectangle frame;
	LPDIRECT3DTEXTURE9 texture;

public:
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texure);

	void draw(int x, int y, D3DCOLOR colorBrush = WHITE(255)) override;
	void drawCenter(int x, int y, D3DCOLOR colorBrush = WHITE(255))override;

	void drawFlip(int x, int y, bool isX = true, D3DCOLOR colorBrush = WHITE(255)) override;
	void drawFlipCenter(int x, int y, bool isX = true, D3DCOLOR colorBrush = WHITE(255)) override;
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
	void add(int id, int idTexture, int left, int top, int right, int bottom);
	LPSPRITE get(int id);
	void deleteAt(int id);
	void clear();
public:
	static CSprites * getInstance();
};

#endif // !_Sprites_H_