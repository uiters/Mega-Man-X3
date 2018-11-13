#include "Tile.h"
#include "Camera.h"
Tile::Tile(int id, LPDIRECT3DTEXTURE9 texture, int x, int y, int width, int height) : CSprite(id, x, y, 0, 0, texture)
{
	this->frame.width = width;
	this->frame.height = height;
	this->x = x;
	this->y = y;
}

Tile::~Tile()
{
}

void Tile::draw(D3DCOLOR colorBrush)
{
	auto pos = cameraGlobal->transformToViewport(x, y);
	CSprite::draw(pos.x, pos.y, colorBrush);
}

void Tile::drawFlip(bool isX, D3DCOLOR colorBrush)
{
	if (isX == true)
	{
		CSprite::drawFlip(x, y, false, colorBrush);
	}
	else CSprite::drawFlip(x, y, false, colorBrush);
}
