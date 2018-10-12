#include "GameObject.h"
#include "Game.h"
GameObject::GameObject(LPCWSTR path, float x, float y, float width , float height) {
	this->x = x;
	this->y = y;
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(path, &info);


	if (result != D3D_OK)
	{
		return;
	}

	this->width = width <= 0 ? info.Width : width;
	this->height = height <= 0 ? info.Height : height;

	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();

	result = D3DXCreateTextureFromFileEx
	(
		d3ddv,								// Pointer to Direct3D device object
		path,						// Path to the image to load
		this->width,							// Texture width
		this->height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),			// Transparent color
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		return;
	}
}


GameObject::~GameObject()
{
	if (texture != NULL) texture->Release();
}
