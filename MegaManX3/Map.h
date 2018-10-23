#pragma once
#include "GameObject.h"
class QuadTree;
class Map
{
private:
	GameObject* mainCharacter;
	LPDIRECT3DTEXTURE9 texture;
public:
	Map(GameObject* mainC, LPDIRECT3DTEXTURE9 tex) : mainCharacter(mainC), texture(tex) {}
	void meo() {
		//QuadTree meo = new QuadTree();
	}
	~Map();
};

