#ifndef _Camera_H
#define _Camera_H

#include "ConstGlobals.h"
#include "Game.h"

class Camera {
public:
	Viewport viewport;
	Rect world;

	Camera();
	Camera(int x, int y, int width, int height);
	void update(int x, int y, int height = 0);

	void setSizeWorld(int left, int top, int right, int bottom);
	void setSizeWorld(int right, int bottom);

	D3DXVECTOR3 transformToViewport(int x, int y);// transform to viewport
};

#endif // _Camera_H_

