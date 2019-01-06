#ifndef _Background_H_
#define _Background_H_
#include "Animation.h"
#include "Camera.h"
#include "ConstGlobals.h"
class Background
{
private:
	float initX, initY;
	UINT width, height;
	bool infinityX, infinityY;

	bool isAnimation;
	CSprite* sprite;
	CAnimation* ani;

	int colStart = 0, colEnd = 0;
	int rowStart = 0, rowEnd = 0;

public:
	Background(UINT id, bool isAnimation, float x, float y, UINT width, UINT height, bool infinityX, bool infinityY);
	~Background();

public:
	void update(Viewport* viewport);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
};

#endif // !_Background_H_