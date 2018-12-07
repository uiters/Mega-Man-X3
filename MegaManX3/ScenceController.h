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
	int rows = 0;
	int cols = 0;
	int width = 0;
	int height = 0;

	int rowStart = 0;
	int rowEnd = 0;
	int colStart = 0;
	int colEnd = 0;

	Tile* ** _tiles; // list scence
	LPDIRECT3DTEXTURE9 _texture;
public:
	ScenceController(int level);
	~ScenceController();
public:
	void update(Viewport *viewport);
	void render(DWORD dt);
};

#endif // !_ScenceController_H_