#include "GameObject.h"
unordered_map<UINT, LPANIMATION> GameObject::_animations;
Collision* GameObject::collision = Collision::getInstance();

GameObject::GameObject(UINT idTexture, int x, int y, float vx, float vy) :speed( vx , vy ) {
	this->x = x;
	this->y = y;

	this->_idObject = idTexture;
	STexture* stexture = texturesGlobal->getSTexture(idTexture);
	
	if (stexture == 0)
	{
		debugOut(L"[FAILED] load texture id = %l", idTexture);
		this->_texture = 0;
		return;
	}
	this->_texture = stexture->texture;

	
}

GameObject::GameObject(UINT id, UINT idTexture, int x, int y, float vx, float vy)
{
	this->x = x;
	this->y = y;

	this->_id = id;
	this->_idObject = idTexture;
	STexture* stexture = texturesGlobal->getSTexture(idTexture);

	if (stexture == 0)
	{
		debugOut(L"[FAILED] load texture id = %l", idTexture);
		this->_texture = 0;
		return;
	}
	this->_texture = stexture->texture;
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



CRectangle* GameObject::getBoundingBox()
{
	float left, top, right, bottom;
	this->getBoundingBox(left, top, right, bottom);
	return &CRectangle::fromLTRB(left, top, right, bottom);
}

void GameObject::update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects)
{
	this->dt = dt;
	dx = speed.vx * dt;
	dy = speed.vy * dt;
	//debugOut(L"%i %i %i %i\n", box.x, box.y, box.width, box.width);
}

GameObject::~GameObject()
{
	//_texture = 0;
	////_animations.clear();
	//if (_texture != NULL) texture->Release();
}
