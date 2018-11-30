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
	//case 3:
	//	//file = LEVEL3;
	//	fileImage = IMAGE_LEVEL3;
	//	break;
	case 4:
		file = LEVEL4;
		fileImage = IMAGE_LEVEL4;
		break;
	//case 5:
	//	//file = LEVEL5;
	//	fileImage = IMAGE_LEVEL5;
	//	break;
	//case 6:
	//	fileImage = IMAGE_LEVEL6;
	//	break;
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
			_tiles[i][j] = new Tile(id, _texture, j * width, h - i * height, width, height);
			debugOut(L"[%i %i]\n", j * width, h - i * height);// , width, height);
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
	colStart = viewport->x / width;
	colStart = colStart > cols ? cols : colStart;

	colEnd = viewport->right() / width + 1;
	colEnd = colEnd > cols ? cols : colEnd;

	rowStart = (rows - viewport->y / width) - 1;
	rowStart = rowStart < 0 ? 0 : rowStart;
	rowEnd = rows - viewport->bottom() / height;

	rowEnd = rowEnd > rows ? rows : rowEnd;



	//colEnd = viewport->right() / width;
	

	//rowStart = rows - (viewport->y - viewport->height) / height;
	
	//debugOut(L"[%i -> %i %i -> % i]\n", rowStart, rowEnd, colStart, colEnd);
	//debugOut(L"[%i %i ]\n", viewport->x, viewport->y);
}

void ScenceController::render(DWORD dt)
{
	for (int i = rowStart; i < rowEnd; ++i)
		for (int j = colStart; j < colEnd; ++j)
			_tiles[i][j]->draw(false);
}
