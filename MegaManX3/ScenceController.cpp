#include "ScenceController.h"
#include "Debugs.h"
#include "Textures.h"
#include "Camera.h"
void ScenceController::calculateIndex(int index, int & left, int & top)
{
	left = (index % colTiles) * width;
	top = (index / colTiles) * height;
}
ScenceController::ScenceController()
{

	texturesGlobal->add(TMap, IMAGE_MAP);
	_texture = texturesGlobal->getTexture(TMap);
	ifstream input;
	input.open(MAP, ifstream::in);
	if (!input.good())
	{
		debugOut(L"[Failed] Load File ");
		return;
	}
	input >> totalFarme >> rows >> cols >> width >> height >> rowTiles >> colTiles;
	int index = 0;
	_tiles = new Tile**[rows];
	int left, top;

	for (int row = 0; row < rows; ++row)
	{
		_tiles[row] = new Tile*[cols];
		for (int col = 0; col < cols; ++col)
		{
			input >> index;
			calculateIndex(index, left, top);
			_tiles[row][col] = new Tile(index, col * width, row * height, left, top, width, height, _texture);
		}

	}
	cameraGlobal->setSizeWorld(0, 0, cols * width, height * height);
	input.close();
}

ScenceController::~ScenceController()
{

	_texture->Release();
	/*for (auto e = _tiles.begin(); e != _tiles.end(); ++e)
	{
		delete e->second;
	}
	_tiles.clear();*/
	
}

void ScenceController::update(Viewport * viewport)
{
	
	colStart = viewport->x / width ;
	colStart = colStart > cols ? cols : colStart;

	colEnd = viewport->right() / width + 1;
	colEnd = colEnd > cols ? cols : colEnd;

	rowStart = viewport->y / height;
	rowStart = rowStart < 0 ? 0 : rowStart;

	rowEnd = viewport->bottom() / height + 2;
	rowEnd = colEnd > rows ? rows : rowEnd;




	//colEnd = viewport->right() / width;
	

	//rowStart = rows - (viewport->y - viewport->height) / height;
	
	//debugOut(L"[%i -> %i %i -> % i]\n", rowStart, rowEnd, colStart, colEnd);
	//debugOut(L"[%i %i ]\n", viewport->x, viewport->y);
}

void ScenceController::render(DWORD dt)
{
	//debugOut(L"%i -> %i  | %i -> %i\n", rowStart, rowEnd, colStart, colEnd);
	for (int row = rowStart; row < rowEnd; ++row)
		for (int col = colStart; col < colEnd; ++col)
			_tiles[row][col]->draw(false);
}
