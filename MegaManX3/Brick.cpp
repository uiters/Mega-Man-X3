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
	D3DXVECTOR3 p(center.x, center.y, 0);
	RECT r;
	r.left = box.left();
	r.top = box.top();
	r.right = box.right();
	r.bottom = box.bottom();
	
	gameGlobal->getSpriteHandler()->Draw(0, &r, NULL, &p, D3DCOLOR_XRGB(128, 255, 255));
	//gameGlobal->getSpriteHandler()->Draw(0, 0, 0,)
}

Brick::~Brick()
{
}
