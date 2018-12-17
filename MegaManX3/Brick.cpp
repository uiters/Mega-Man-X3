#include "Brick.h"

Brick::Brick(UINT id, int x, int y, int width, int height) : StaticObject(id, x, y, width, height)
{

}
#include "Camera.h"
void Brick::render(DWORD dt, D3DCOLOR colorBrush)
{
	//auto center = cameraGlobal->transform(x, y);
	////drawLine(gameGlobal->getDirect3DDevice(), center.x, center.y, D3DCOLOR_XRGB(0, 0, 255));

}
void Brick::drawLine(LPDIRECT3DDEVICE9 Device_Interface, int x, int y, D3DCOLOR color)
{
	gameGlobal->getSpriteHandler()->End();
	D3DRECT rec = { x, y, x + width, y + height };
	
	Device_Interface->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
	gameGlobal->getSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);
}

Brick::~Brick()
{
}

