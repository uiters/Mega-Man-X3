#include "Sprites.h"

CSprite::CSprite()
{
}

CSprite::CSprite(UINT id, UINT left, UINT top, UINT right, UINT bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	frame = CRectangle::fromLTRB(left, top, right, bottom);

	this->texture = tex;
}

void CSprite::draw(float x, float y, bool center, D3DCOLOR colorBrush)
{
	D3DXVECTOR3 pos(x, y, 0);
	if (center) 
	{
		D3DXVECTOR3 center(frame.width / 2, frame.height / 2, 0);
		gameGlobal->getSpriteHandler()->Draw(texture, &frame.getRECT(), &center, &pos, colorBrush);
	}
	else
	{
		gameGlobal->getSpriteHandler()->Draw(texture, &frame.getRECT(), 0, &pos, colorBrush);
	}
	
}


void CSprite::drawFlipX(float x, float y, bool center, D3DCOLOR colorBrush)
{
	LPD3DXSPRITE spriteHandler = gameGlobal->getSpriteHandler();
	D3DXMATRIX newMatrix;
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1 , 1);
	D3DXVECTOR2 center2 = D3DXVECTOR2(x + frame.width / 2, y + frame.height / 2);
	D3DXMATRIX oldMatrix;
	spriteHandler->GetTransform(&oldMatrix);

	D3DXMatrixTransformation2D(&newMatrix, &center2, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMatrix = newMatrix * oldMatrix;
	spriteHandler->SetTransform(&finalMatrix);
	this->draw(x, y, center, colorBrush);
	spriteHandler->SetTransform(&oldMatrix);
}

void CSprite::drawFlipY(float x, float y, bool center, D3DCOLOR colorBrush)
{
	LPD3DXSPRITE spriteHandler = gameGlobal->getSpriteHandler();
	D3DXMATRIX newMatrix;
	D3DXVECTOR2 rotate = D3DXVECTOR2(1, -1);
	D3DXVECTOR2 center2 = D3DXVECTOR2(x + frame.width / 2, y + frame.height / 2);
	D3DXMATRIX oldMatrix;
	spriteHandler->GetTransform(&oldMatrix);

	D3DXMatrixTransformation2D(&newMatrix, &center2, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMatrix = newMatrix * oldMatrix;
	spriteHandler->SetTransform(&finalMatrix);
	this->draw(x, y, center, colorBrush);
	spriteHandler->SetTransform(&oldMatrix);
}

Size CSprite::getSize()
{
	return frame.getSize();
}


CSprites * CSprites::__instance = NULL;

CSprites *CSprites::getInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprites::add(UINT id, UINT idTexture, UINT left, UINT top, UINT right, UINT bottom)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, texturesGlobal->getTexture(idTexture));

	sprites[id] = s;
}

void CSprites::addSprite(UINT id, UINT idTexture, UINT x, UINT y, UINT width, UINT height)
{
	CRectangle rect(x, y, width, height);
	LPSPRITE s = new CSprite(id, rect.left(), rect.top(), rect.right(), rect.bottom(), texturesGlobal->getTexture(idTexture));

	sprites[id] = s;
}

LPSPRITE CSprites::get(UINT id)
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

void CSprites::deleteAt(UINT id)
{
	if (sprites[id] == 0)
	{
		debugOut(L"[FAILED] Delete Sprite");
		return;
	}
	delete sprites[id];
	sprites.erase(id);
}
