#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "Game.h"
#include "textures.h"

CTextures * CTextures::__instance = NULL;


CTextures *CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}

void CTextures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
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
		return;
	}



	textures[id] = { texture,(float) info.Width,(float) info.Height };

}

LPDIRECT3DTEXTURE9 CTextures::GetTexture(unsigned int i)
{
	return textures[i].texture;
}

void CTextures::GetSize(UINT id, float & width, float & height)
{
	height = textures[id].height;
	width = textures[id].width;
}


void CTextures::DelTexture(UINT id)
{
	textures[id].texture->Release();
	textures.erase(id);
}

void CTextures::Clear()
{
	for (auto i : textures)
	{
		i.second.texture->Release();
		textures.erase(i.first);
	}
}



