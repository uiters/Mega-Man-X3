#include "Sprites.h"
#include "Game.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::getInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::draw(float x, float y, D3DCOLOR colorBrush)
{
	D3DXVECTOR3 pos(x, y, 0);
	RECT sRect = { left, top, right, bottom };

	gameGlobal->getSpriteHandler()->Draw(texture, &sRect, NULL, &pos, colorBrush);
}

void CSprite::drawFlip(int x, int y, bool isLeft, float width, float height, D3DCOLOR colorBrush)
{
	auto spriteHandler = gameGlobal->getSpriteHandler();
	D3DXVECTOR3 pos(x, y, 0);
	RECT sRect = { left, top, right, bottom };

	D3DXMATRIX oldMatrix;
	spriteHandler->GetTransform(&oldMatrix);

	D3DXMATRIX newMatrix;
	D3DXVECTOR2 center = D3DXVECTOR2(x + width / 2, y + height / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(isLeft ? 1 : -1, 1);

	D3DXMatrixTransformation2D(&newMatrix, &center, 0.0f, &rotate, 0, 0.0f, 0);
	D3DXMATRIX finalMatrix = newMatrix * oldMatrix;
	spriteHandler->SetTransform(&finalMatrix);

	spriteHandler->Draw(texture, &sRect, 0, &pos, colorBrush);

	spriteHandler->SetTransform(&oldMatrix);
}

void CSprites::add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
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
		if(i.second != 0)
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
