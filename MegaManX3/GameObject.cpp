#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(UINT idTexture, float x, float y, float vx, float vy) :speed( vx , vy ) {
	this->x = x;
	this->y = y;


	this->_id = idTexture;
	STexture* stexture = texturesGlobal->getSTexture(idTexture);
	if (stexture == 0)
	{
		debugOut(L"[FAILED] load texture id = %l", idTexture);
		this->_texture = 0;
		this->_width = this->_height = 0;
		return;
	}
	this->_texture = stexture->texture;
	this->_width = stexture->width;
	this->_height = stexture->height;
}

LPDIRECT3DTEXTURE9 GameObject::getTexture()
{
	return _texture;
}

void GameObject::getSize(float & width, float & height)
{
	width = this->_width;
	height = this->_height;
}

int GameObject::getState()
{
	return _state;
}

bool GameObject::canReset()
{
	return _canReset;
}

bool GameObject::canRemove()
{
	return _canRemove;
}

bool GameObject::canDamage()
{
	return _canDamage;
}

void GameObject::addAnimation(UINT animationId)
{
	LPANIMATION ani = animationsGlobal->get(animationId);
	_animations.push_back(ani);
}

void GameObject::renderBoundingBox()
{

	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	//LPDIRECT3DTEXTURE9 bbox = texturesGlobal->getTexture(ID_TEX_BBOX);

	float l, t, r, b;

	getBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	draw(x, y, NULL, rect.left, rect.top, rect.right, rect.bottom, 32);
}

ObjectType GameObject::getType()
{
	return type;
}




void GameObject::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _width;
	bottom = y + _height;
}

RECT GameObject::getBoundingBox()
{
	return { (long)x, (long)y, (long)(x + _width), (long)(y + _height) };
}

void GameObject::setState(UINT state)
{
	_state = state;
}

void GameObject::update(DWORD dt, vector<LPObject>* coObjects)
{
	this->dt = dt;
	dx = speed.vx * dt;
	dy = speed.vy * dt;
}

GameObject::~GameObject()
{
	//_texture = 0;
	//_animations.clear();
	//if (texture != NULL) texture->Release();
}
