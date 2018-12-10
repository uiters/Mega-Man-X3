#include "ScenceController.h"
#include "Debugs.h"
#include "Textures.h"
#include "Camera.h"
ScenceController::ScenceController(int level)
{
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
	level *= -1;
	texturesGlobal->add(level, fileImage);
	_texture = texturesGlobal->getTexture(level);
	ifstream input;
	input.open(file, ifstream::in);
	if (!input.good())
	{
		debugOut(L"[Failed] Load File ");
		return;
	}
	input >> totalFarme >> rows >> cols >> width >> height;
	int id = 0;
	_tiles = new Tile**[rows];

	for (int row = 0; row < rows; ++row)
	{
		_tiles[row] = new Tile*[cols];
		for (int col = 0; col < cols; ++col)
		{
			input >> id;
			_tiles[row][col] = new Tile(id, _texture, col * width, row * height, width, height);
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
	for (int row = rowStart; row < rowEnd; ++row)
		for (int col = colStart; col < colEnd; ++col)
			_tiles[row][col]->draw(false);
}
