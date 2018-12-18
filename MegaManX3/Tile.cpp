#include "Tile.h"
#include "Camera.h"
Tile::Tile(UINT index, LPDIRECT3DTEXTURE9 texture, int x, int y, UINT width, UINT height)
{
	this->id = index;
	this->texture = texture;
	this->x = x;
	this->y = y;
	//this->frame = CRectangle(index * width, 0, width, height);
	this->frame.x = index * width;
	this->frame.y = 0;
	this->frame.width = width;
	this->frame.height = height;
	//debugOut(L"%i\t\t[%i, %i %i %i]\t\t", index, this->frame.x, this->frame.y, this->frame.right(), this->frame.bottom());
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