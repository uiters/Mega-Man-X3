#ifndef _Tile_H_
#define _Tile_H_

#include "Sprites.h"
class Tile :
	private CSprite
{
public:
	int x;
	int y;
public:
	Tile(UINT id, LPDIRECT3DTEXTURE9 texture, int x, int y, UINT width, UINT heigt);// id = index 
	~Tile();
	void draw(bool center, D3DCOLOR colorBrush = WHITE(255));
	void drawFlipX(bool center, D3DCOLOR colorBrush = WHITE(255));
	void drawFlipY(bool center, D3DCOLOR colorBrush = WHITE(255));
};

#endif // !_Title_H_