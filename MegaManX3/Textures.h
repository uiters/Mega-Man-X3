#pragma once
#include <unordered_map>
#include <d3dx9.h>
#include "ConstColor.h"

using namespace std;

/*
	Manage texture database
*/

struct STexture
{
	LPDIRECT3DTEXTURE9 texture;
	float width;
	float height;
};

class CTextures
{
	static CTextures * __instance;

	unordered_map<int, STexture> textures;

public:
	CTextures() {}
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor = BLACK(0));
	LPDIRECT3DTEXTURE9 GetTexture(unsigned int i);
	void GetSize(UINT id, float &width, float &height);
	void DelTexture(UINT id);
	void Clear();


	static CTextures * GetInstance();
};

