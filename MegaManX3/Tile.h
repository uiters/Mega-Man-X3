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
	Tile(int id, LPDIRECT3DTEXTURE9 texture, int x, int y, int width, int heigt);// id = index 
	~Tile();
	void draw(D3DCOLOR colorBrush = WHITE(255));
	void drawFlip(bool isX, D3DCOLOR colorBrush = WHITE(255));
};

#endif // !_Title_H_