#include "Sprites.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	frame = CRectangle::fromLTRB(left, top, right, bottom);

	this->texture = tex;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::getInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}



void CSprite::draw(int x, int y, D3DCOLOR colorBrush)
{
	D3DXVECTOR3 pos(x, y, 0);
	_draw(texture, &frame.getRECT(), 0, &pos, colorBrush);
}

void CSprite::drawCenter(int x, int y, D3DCOLOR colorBrush)
{
	D3DXVECTOR3 pos(x, y, 0);
	D3DXVECTOR3 center(frame.width / 2, frame.height / 2, 0);

	_draw(texture, &frame.getRECT(), &center, &pos, colorBrush);
}

void CSprite::drawFlip(int x, int y, bool isX, D3DCOLOR colorBrush)
{
	LPD3DXSPRITE spriteHandler = gameGlobal->getSpriteHandler();
	D3DXVECTOR3 pos(x, y, 0);

	D3DXMATRIX oldMatrix;
	spriteHandler->GetTransform(&oldMatrix);

	D3DXMATRIX newMatrix;
	D3DXVECTOR2 center = D3DXVECTOR2(x + frame.width / 2, y + frame.height / 2);
	int bit = isX ? -1 : 1;
	D3DXVECTOR2 rotate = D3DXVECTOR2(bit, bit * -1);

	D3DXMatrixTransformation2D(&newMatrix, &center, 0.0f, &rotate, 0, 0.0f, 0);
	D3DXMATRIX finalMatrix = newMatrix * oldMatrix;
	spriteHandler->SetTransform(&finalMatrix);

	_draw(texture, &frame.getRECT(), 0, &pos, colorBrush);

	spriteHandler->SetTransform(&oldMatrix);
}

void CSprite::drawFlipCenter(int x, int y, bool isX, D3DCOLOR colorBrush)
{
	LPD3DXSPRITE spriteHandler = gameGlobal->getSpriteHandler();
	D3DXVECTOR3 pos(x, y, 0);
	D3DXVECTOR3 center3(frame.width / 2, frame.height / 2, 0);

	D3DXMATRIX oldMatrix;
	spriteHandler->GetTransform(&oldMatrix);

	D3DXMATRIX newMatrix;
	D3DXVECTOR2 center = D3DXVECTOR2(x + frame.width / 2, y + frame.height / 2);
	int bit = isX ? -1 : 1;
	D3DXVECTOR2 rotate = D3DXVECTOR2(bit, bit * -1);

	D3DXMatrixTransformation2D(&newMatrix, &center, 0.0f, &rotate, 0, 0.0f, 0);
	D3DXMATRIX finalMatrix = newMatrix * oldMatrix;
	spriteHandler->SetTransform(&finalMatrix);

	_draw(texture, &frame.getRECT(), &center3, &pos, colorBrush);

	spriteHandler->SetTransform(&oldMatrix);
}


void CSprites::add(int id, int idTexture, int left, int top, int right, int bottom)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, texturesGlobal->getTexture(idTexture));

	sprites[id] = s;
}

LPSPRITE CSprites::get(int id)
{
	return sprites[id];
}

void CSprites::clear()
{
	for (auto i : sprites)
	{
		if (i.second != 0)
			delete i.second;
	}
	sprites.clear();
}

void CSprites::deleteAt(int id)
{
	if (sprites[id] == 0)
	{
		debugOut(L"[FAILED] Delete Sprite");
		return;
	}
	delete sprites[id];
	sprites.erase(id);
}
