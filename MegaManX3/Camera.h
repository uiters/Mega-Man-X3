#ifndef _Camera_H
#define _Camera_H

#include "ConstGlobals.h"
#include "Game.h"

class Camera {
public:
	Viewport viewport;
	Rect world;

	Camera(int x, int y, int width, int height);
	void update(int x, int y);

	void setSizeWorld(int x,int y,int width,int height);

	const Point transform(const int& x,const int& y) const;
	//D3DXVECTOR3 transformToViewport(int x, int y);// transform to viewport
};

#endif // _Camera_H_

