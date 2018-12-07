#include "Brick.h"

Brick::Brick(UINT id, int x, int y, int width, int height)
{
	this->_id = id;
	this->box.x = x;
	this->box.y = y;
	this->box.width = width;
	this->box.height = height;
	this->x = x;
	this->y = y;
}
#include "Camera.h"
void Brick::render(DWORD dt, D3DCOLOR colorBrush)
{
	auto center = cameraGlobal->transform(x, y);
	//D3DXVECTOR3 p(center.x, center.y, 0);
	//RECT rect;
	//float l, t, r, b;

	//GameObject::getBoundingBox(l, t, r, b);
	//rect.left = 0;
	//rect.top = 0;
	//rect.right = (int)r - (int)l;
	//rect.bottom = (int)b - (int)t;
	//
	//gameGlobal->getSpriteHandler()->Draw(texturesGlobal->getTexture(-100), 0, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));*/
	////gameGlobal->getSpriteHandler()->Draw(0, 0, 0,)
	drawLine(gameGlobal->getDirect3DDevice(), center.x, center.y, D3DCOLOR_XRGB(0, 0, 255));
	//drawLine(gameGlobal->getDirect3DDevice(), center.x, center.y + box.height, box.width, D3DCOLOR_XRGB(255, 0, 255));
	//drawLine(gameGlobal->getDirect3DDevice(), center.x, center.y, box.width, D3DCOLOR_XRGB(255, 0, 255));
	//drawLine(gameGlobal->getDirect3DDevice(), center.x, center.y, box.width, D3DCOLOR_XRGB(255, 0, 255));
}
void Brick::drawLine(LPDIRECT3DDEVICE9 Device_Interface, int x, int y, D3DCOLOR color)
{
	gameGlobal->getSpriteHandler()->End();
	D3DRECT rec = { x, y, x + box.width, y + box.height };
	
	Device_Interface->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
	gameGlobal->getSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);
}

Brick::~Brick()
{
}
