#include "Camera.h"
Camera::Camera() :viewport(0, 0, WD_WIDTH, WD_HEIGHT)
{
}

Camera::Camera(float x, float y, float width, float height): viewport(x, y, width, height)
{

}

void Camera::setSizeWorld(float left, float top, float right, float bottom)
{
	world.left = left;
	world.right = right;
	world.top = top;
	world.bottom = bottom;
}

void Camera::setSizeWorld(float right, float top)
{
	world.left = 0;
	world.top = top;
	world.right = right;
	world.bottom = 0;
}



D3DXVECTOR3 Camera::transformToViewport(float x, float y) {
	D3DXVECTOR3 pos3(x, y, 1); // ma tran x
	D3DXMATRIX matrix; // 
	D3DXVECTOR4 matrixResult; // ma tran ket qua
	D3DXMatrixIdentity(&matrix);

	matrix._22 = -1.0f;
	matrix._41 = -viewport.x;
	matrix._42 = viewport.y;

	D3DXVec3Transform(&matrixResult, &pos3, &matrix);

	return D3DXVECTOR3(matrixResult.x, matrixResult.y, 0);
}

void Camera::update(float x, float y, float height) //center x, center y
{
	float centerScreenX = viewport.width / 2;
	float centerScreenY = viewport.height / 2;

	viewport.x = x - centerScreenX; // hold character center of camera
	viewport.y = y + centerScreenY;

	if (viewport.x < world.left)
		viewport.x = world.left;

	if (viewport.right() > world.right)
		viewport.setRight(world.right);

	if (viewport.y > world.top)
		viewport.y = world.top;

	if (viewport.bottom() < world.bottom - height / 4)
		viewport.setBottom(world.bottom - height / 4);
}