#ifndef _Graphics_h_
#define _Graphics_h_
#include <d3d9.h>
#include <d3dx9.h>
#include "Game.h"
#include "ConstGlobals.h"


void draw(float x, float y, LPDIRECT3DTEXTURE9 texture, D3DCOLOR colorBrush = WHITE(255));
void draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, D3DCOLOR colorBrush = WHITE(255));
void draw(LPDIRECT3DTEXTURE9 texture, RECT* srect, D3DXVECTOR3* center, D3DXVECTOR3 pos, D3DCOLOR colorBrush = WHITE(255));
void drawFlipX(int x, int y, LPDIRECT3DTEXTURE9 texture, float width, float height, D3DCOLOR colorBrush = WHITE(255));

#endif // !_Graphics.h_
