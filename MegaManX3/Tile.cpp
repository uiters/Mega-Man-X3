#include "Tile.h"
#include "Camera.h"
Tile::Tile(UINT id, LPDIRECT3DTEXTURE9 texture, int x, int y, UINT width, UINT height) : CSprite(id, id * width, 0, (id + 1) * width, height, texture)
{
	//this->frame.width = width;
	//this->frame.height = height;
	//this->frame.x = ;
	//this->frame.y = ;
	this->x = x;
	this->y = y;
	//debugOut(L"[%i, %i] [%u %u]\n", x, y, width, height);
}

Tile::~Tile()
{
}

void Tile::draw(bool center, D3DCOLOR colorBrush)
{
	
	auto pos = cameraGlobal->transformToViewport(x, y);
	//debugOut(L"[%f, %f] [%f, %f]\n", x, y, pos.x, pos.y);
	CSprite::draw(pos.x, pos.y, center,  colorBrush);
}

void Tile::drawFlipX(bool center, D3DCOLOR colorBrush)
{
	auto pos = cameraGlobal->transformToViewport(x, y);
	CSprite::drawFlipX(pos.x, pos.y, center, colorBrush);
}

void Tile::drawFlipY(bool center, D3DCOLOR colorBrush)
{
	auto pos = cameraGlobal->transformToViewport(x, y);
	CSprite::drawFlipY(pos.x, pos.y, center, colorBrush);
}