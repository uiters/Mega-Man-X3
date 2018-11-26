#pragma once
#include <unordered_map>
#include "Game.h"
#include "Debugs.h"
using namespace std;

/*
	Manage texture database
*/
struct STexture
{
	LPDIRECT3DTEXTURE9 texture;
	UINT width;
	UINT height;
};

class CTextures
{
	static CTextures * __instance;
	unordered_map<unsigned int, STexture*> textures;

public:
	void add(UINT id, LPCWSTR filePath, UINT width = 0, UINT height = 0, D3DCOLOR transparentColor = BLACK(0));
	LPDIRECT3DTEXTURE9 getTexture(UINT id);
	void getSize(UINT id, UINT &width, UINT &height);
	STexture* getSTexture(UINT id);
	void deleteAt(UINT id);
	void clear();

	static CTextures * getInstance();

};
