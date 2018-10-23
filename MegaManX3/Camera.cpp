#include "Camera.h"
Camera::Camera()
{
	viewport.x = 1;
	viewport.y = WD_HEIGHT;
}
void Camera::SetSize(float max, float min) {
	right = max;
	left = min;
}

D3DXVECTOR2 Camera::Transform(float x, float y) {
	D3DXVECTOR3 pos3(x, y, 1); // ma tran x
	D3DXMATRIX matrix; // 
	D3DXVECTOR4 matrixResult; // ma tran ket qua

	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._41 = -viewport.x;
	matrix._42 = viewport.y;
	D3DXVec3Transform(&matrixResult, &pos3, &matrix);
	D3DXVECTOR2 result = D3DXVECTOR2(matrixResult.x, matrixResult.y);
	return result;
}