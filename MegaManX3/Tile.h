#ifndef _Tile_H_
#define _Tile_H_

#include "Sprites.h"
class Tile :
	private CSprite
{
private:
	int x;
	int y;
public:
	
	Tile(UINT index, int x, int y, int left, int top, UINT width, UINT height, LPDIRECT3DTEXTURE9 texture);

	~Tile();
	void draw(bool center, D3DCOLOR colorBrush = WHITE(255));
	void drawFlipX(bool center, D3DCOLOR colorBrush = WHITE(255));
	void drawFlipY(bool center, D3DCOLOR colorBrush = WHITE(255));
};

#endif // !_Title_H_