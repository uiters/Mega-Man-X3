#include "GameObject.h"
unordered_map<UINT, LPANIMATION> GameObject::_animations;
Collision* GameObject::collision = Collision::getInstance();
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

GameObject::GameObject(UINT id, UINT idTexture, int x, int y, float vx, float vy)
{
	this->x = x;
	this->y = y;

	this->_id = id;
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

ObjectType GameObject::getType()
{
	return type;
}

void GameObject::getBoundingBox(float &left, float& top, float& right, float& bottom) {
	left = box.x;
	top = box.y;
	right = box.right();
	bottom = box.bottom();
}

void GameObject::clone(GameObject * object, int id, int x, int y, int width, int height)
{
	this->box.x = x;
	this->box.y = y;
	this->box.width = width;
	this->box.height = height;
	this->type = object->type;
	this->_animations = object->_animations;
}

CRectangle* GameObject::getBoundingBox()
{
	return &box;
}

void GameObject::updateBox()
{
	this->box.x = this->x;
	this->box.y = this->y;
	Size size = _animations[state]->getSize();
	this->box.width = size.width;
	this->box.height = size.height;
}


void GameObject::update(DWORD dt, unordered_map<int, CTreeObject*>* staticObjects, unordered_map<int, CTreeObject*>* dynamicObjects)
{
	updateBox();
	this->dt = dt;
	dx = speed.vx * dt;
	dy = speed.vy * dt;
	//debugOut(L"%i %i %i %i\n", box.x, box.y, box.width, box.width);
}

GameObject::~GameObject()
{
	//_texture = 0;
	//_animations.clear();
	//if (texture != NULL) texture->Release();
}
