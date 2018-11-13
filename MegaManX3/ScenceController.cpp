#include "ScenceController.h"
#include "Debugs.h"
#include "Textures.h"

ScenceController::ScenceController(int level, int width, int height)
{
	this->width = width;
	this->height = height;
	wchar_t* file;
	wchar_t* fileImage;
	switch (level)
	{
	case 1:
		file = LEVEL1;
		fileImage = IMAGE_LEVEL1;
		break;
	case 2:
		file = LEVEL2;
		fileImage = IMAGE_LEVEL2;
		break;
	case 3:
		file = LEVEL3;
		fileImage = IMAGE_LEVEL3;
		break;
	case 4:
		file = LEVEL4;
		fileImage = IMAGE_LEVEL4;
		break;
	case 5:
		file = LEVEL5;
		fileImage = IMAGE_LEVEL5;
		break;
	default:
		fileImage = IMAGE_LEVEL1;
		file = LEVEL1;
		break;
	}

	texturesGlobal->add(-10, fileImage);
	_texture = texturesGlobal->getTexture(-10);
	ifstream input;
	input.open(file, ifstream::in);
	if (!input.good())
	{
		debugOut(L"[Failed] Load File %w", file);
		return;
	}
	input >> totalFarme >> rows >> cols;
	int id = 0;
	_tiles = new Tile**[rows];
	int h = height * rows;
	int w = width * cols;

	for (int i = 0; i < rows; ++i)
	{
		_tiles[i] = new Tile*[cols];
		for (int j = 0; j < cols; ++j)
		{
			input >> id;
			_tiles[i][j] = new Tile(id, _texture, i * width, w - j * height, width, height);
		}
	}

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
	
}

void ScenceController::render(DWORD dt)
{
	//for (CTemp* i : _currentTiles)
	//{
	//	i->draw();
	//}
}
