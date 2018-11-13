#ifndef _ScenceController_H_
#define _ScenceController_H_

#include <fstream>

#include "ConstGlobals.h"
#include "Tile.h"
#include "QNode.h"

using namespace std;

class ScenceController
{
protected:
	int totalFarme;
	int rows;
	int cols;
	int width = 64;
	int height = 64;

	Tile* ** _tiles; // list scence
	LPDIRECT3DTEXTURE9 _texture;
public:
	ScenceController(int level, int width = 64, int height = 64);
	~ScenceController();
public:
	void update(Viewport *viewport);
	void render(DWORD dt);
};

#endif // !_ScenceController_H_