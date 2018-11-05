#ifndef _Camera_H
#define _Camera_H

#include "ConstGlobals.h"
#include <d3d9.h>
#include <d3dx9.h>

class Camera {
public:
	Viewport viewport;
	Rect world;

	Camera();
	Camera(float x, float y, float width, float height);
	void update(float x, float y);

	void setSizeWorld(float left, float top, float right, float bottom);
	void setSizeWorld(float right, float bottom);

	D3DXVECTOR3 transformToViewport(float x, float y);// transform to viewport
};
#endif // _Camera_H_

