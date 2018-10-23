#define _Camera_H
#ifdef _Camera_H
#include "ConstGlobals.h"
#include <d3d9.h>
#include <d3dx9.h>
class Camera {
public:
	D3DXVECTOR2 viewport;
	float right, left;

	Camera();
	void Update(float x, float y);
	void SetSize(float max, float min);
	D3DXVECTOR2 Transform(float x, float y);
};
#endif // _Camera_H

