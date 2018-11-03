#include "Graphics.h"

void draw(float x, float y, LPDIRECT3DTEXTURE9 texture, D3DCOLOR colorBrush) {
	D3DXVECTOR3 p(x, y, 0);
	gameGlobal->getSpriteHandler()->Draw(texture, NULL, NULL, &p, colorBrush);
}

void draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, D3DCOLOR colorBrush)
{
	D3DXVECTOR3 p(x, y, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	gameGlobal->getSpriteHandler()->Draw(texture, &r, NULL, &p, colorBrush);
}

void drawFlipX(int x, int y, LPDIRECT3DTEXTURE9 texture, float width, float height, D3DCOLOR colorBrush)
{
	LPD3DXSPRITE spriteHandler = gameGlobal->getSpriteHandler();

	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + width / 2, y + height / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	spriteHandler->SetTransform(&finalMt);

	x += width;
	draw(x, y, texture, colorBrush);

	spriteHandler->SetTransform(&oldMt);
}