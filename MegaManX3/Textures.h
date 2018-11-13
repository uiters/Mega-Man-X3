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
	float width;
	float height;
};

class CTextures
{
	static CTextures * __instance;

	unordered_map<int, STexture*> textures;

public:
	void add(int id, LPCWSTR filePath, float width = 0, float height = 0, D3DCOLOR transparentColor = BLACK(0));
	LPDIRECT3DTEXTURE9 getTexture(int id);
	void getSize(int id, int &width, int &height);
	STexture* getSTexture(int id);
	void deleteAt(int id);
	void clear();

	static CTextures * getInstance();

};
