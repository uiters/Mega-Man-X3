#include "Background.h"
Background::Background(UINT id, bool isAnimation, float x, float y, UINT width, UINT height, bool infinityX, bool infinityY)
{
	this->isAnimation = isAnimation;
	initX = x;
	initY = y;
	if (isAnimation)
		ani = animationsGlobal->get(id);
	else
		sprite = spritesGlobal->get(id);
	this->width = width;
	this->height = height;
	this->infinityX = infinityX;
	this->infinityY = infinityY;
}

Background::~Background()
{
}

void Background::update(Viewport * viewport)
{
	colStart = (viewport->x - initX) / width - 0.9999f; //sure
	rowStart = (viewport->y - initY) / height - 0.9999f; // sure

	colEnd = infinityX ? (viewport->right() - initX) / (float)width + 1.49999f : 1;
	rowEnd = infinityY ? (viewport->bottom() - initY) / (float)height + 0.99999f : 1;
}

void Background::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (viewPortGlobal->right() < initX || viewPortGlobal->bottom() < initY) 
		return;
	float x = 0, y = 0;
	for (int row = rowStart; row < rowEnd; ++row)
		for (int col = colStart; col < colEnd; ++col)
		{
			x = initX + col * width;
			y = initY + row * height;
			auto pos = &cameraGlobal->transform(x, y);
			if (isAnimation)
				ani->render(pos->x, pos->y);
			else
				sprite->draw(pos->x, pos->y);
		}
}
