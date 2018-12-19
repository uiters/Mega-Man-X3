#include "Tile.h"
#include "Camera.h"

Tile::Tile(UINT index, int x, int y, int left, int top, UINT width, UINT height, LPDIRECT3DTEXTURE9 texture)
{
	this->id = index;
	this->x = x;
	this->y = y;
	this->texture = texture;
	this->frame.x = left;
	this->frame.y = top;
	this->frame.width = width;
	this->frame.height = height;
}

Tile::~Tile()
{
}

void Tile::draw(bool center, D3DCOLOR colorBrush)
{
	
	auto pos = cameraGlobal->transform(x, y);
	CSprite::draw(pos.x, pos.y, center,  colorBrush);
	//CSprite::draw(0, 0, center, colorBrush);
}

void Tile::drawFlipX(bool center, D3DCOLOR colorBrush)
{
	auto pos = cameraGlobal->transform(x, y);
	CSprite::drawFlipX(pos.x, pos.y, center, colorBrush);
}

void Tile::drawFlipY(bool center, D3DCOLOR colorBrush)
{
	auto pos = cameraGlobal->transform(x, y);
	CSprite::drawFlipY(pos.x, pos.y, center, colorBrush);
}