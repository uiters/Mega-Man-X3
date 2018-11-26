#include "Textures.h"

CTextures * CTextures::__instance = NULL;


CTextures *CTextures::getInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}


void CTextures::add(UINT id, LPCWSTR filePath, UINT width, UINT height, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		debugOut(L"[FAILED] Create Image");
		return;
	}
	width = width > 0 ? width : info.Width;
	height = height > 0 ? height : info.Height;

	LPDIRECT3DDEVICE9 d3ddv = gameGlobal->getDirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		width,							// Texture width
		height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		debugOut(L"[FAILED] create texture");
		return;
	}
	textures[id] = new STexture{ texture, width, height };
}

LPDIRECT3DTEXTURE9 CTextures::getTexture(UINT id)
{
	return textures[id]->texture;
}

void CTextures::getSize(UINT id, UINT& width, UINT& height)
{
	height = textures[id]->height;
	width = textures[id]->width;
}

STexture* CTextures::getSTexture(UINT id)
{
	return textures[id];
}


void CTextures::deleteAt(UINT id)
{
	textures[id]->texture->Release();
	textures.erase(id);
}

void CTextures::clear()
{
	for (auto i : textures)
	{
		if (i.second != 0)
			i.second->texture->Release();
	}
	textures.clear();
}
