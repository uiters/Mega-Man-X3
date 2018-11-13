#include "Camera.h"

Camera::Camera() :viewport(0, 0, WD_WIDTH, WD_HEIGHT)
{
}

Camera::Camera(int x, int y, int width, int height) : viewport(x, y, width, height)
{

}

void Camera::setSizeWorld(int left, int top, int right, int bottom)
{
	world.left = left;
	world.right = right;
	world.top = top;
	world.bottom = bottom;
}

void Camera::setSizeWorld(int top, int right)
{
	world.left = 0;
	world.top = top;
	world.right = right;
	world.bottom = 0;
}



D3DXVECTOR3 Camera::transformToViewport(int x, int y) {
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

void Camera::update(int x, int y, int height) //center x, center y
{
	int centerScreenX = viewport.width / 2;
	int centerScreenY = viewport.height / 2;

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
