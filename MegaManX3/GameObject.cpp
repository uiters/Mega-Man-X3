#include "GameObject.h"

GameObject::GameObject(UINT idTexture, int x, int y, float vx, float vy) :speed( vx , vy ) {
	this->x = x;
	this->y = y;

	this->_id = idTexture;
	STexture* stexture = texturesGlobal->getSTexture(idTexture);
	
	if (stexture == 0)
	{
		debugOut(L"[FAILED] load texture id = %l", idTexture);
		this->_texture = 0;
		this->box.width = this->box.height = 0;
		return;
	}
	this->_texture = stexture->texture;
	this->box.height = stexture->width;
	this->box.width = stexture->height;
}

LPDIRECT3DTEXTURE9 GameObject::getTexture()
{
	return _texture;
}

void GameObject::getSize(int & width, int & height)
{
	width = this->box.width;
	height = this->box.height;
}

bool GameObject::canReset()
{
	return _canReset;
}

bool GameObject::canRemove()
{
	return _canRemove;
}


void GameObject::addAnimation(UINT animationId)
{
	LPANIMATION ani = animationsGlobal->get(animationId);
	_animations[animationId] = ani;
}

//void GameObject::renderBoundingBox()
//{
//
//	D3DXVECTOR3 p(x, y, 0);
//	RECT rect;
//
//	//LPDIRECT3DTEXTURE9 bbox = texturesGlobal->getTexture(ID_TEX_BBOX);
//
//	int l, t, r, b;
//
//	getBoundingBox(l, t, r, b);
//	rect.left = 0;
//	rect.top = 0;
//	rect.right = (int)r - (int)l;
//	rect.bottom = (int)b - (int)t;
//
////	draw(x, y, NULL, rect.left, rect.top, rect.right, rect.bottom, 32);
//}

ObjectType GameObject::getType()
{
	return type;
}

void GameObject::getBoundingBox(int &left, int& top, int& right, int& bottom) {
	left = box.x;
	top = box.y;
	right = box.right();
	bottom = box.bottom();
}

CRectangle* GameObject::getBoundingBox()
{
	return &box;
}

void GameObject::updateBox()
{
	this->box.x = this->x;
	this->box.y = this->y;
	if (_animations.size() != 0)
	{
		Size size = _animations[state]->getSize();
		this->box.width = size.width;
		this->box.height = size.height;
	}
}


void GameObject::update(DWORD dt, vector<LPObject>* coObjects)
{
	this->dt = dt;
	dx = speed.vx * dt;
	dy = speed.vy * dt;
	//updateBox();
}

GameObject::~GameObject()
{
	//_texture = 0;
	//_animations.clear();
	//if (texture != NULL) texture->Release();
}
