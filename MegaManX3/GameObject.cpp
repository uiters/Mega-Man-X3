#include "GameObject.h"
#include "Game.h"
GameObject::GameObject(UINT idTexture, float x, float y, float vx, float vy, float width, float height) :speed( vx , vy ) {
	this->x = x;
	this->y = y;

	this->width = width;
	this->height = height;
	this->_id = idTexture;

	this->texture = CTextures::getInstance()->getTexture(idTexture);
}

void GameObject::getSize(float & width, float & height)
{
	width = this->width;
	height = this->height;
}

void GameObject::addAnimation(UINT animationId)
{
	LPANIMATION ani = CAnimations::getInstance()->get(animationId);
	animations.push_back(ani);
}

void GameObject::renderBoundingBox()
{

	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::getInstance()->getTexture(ID_TEX_BBOX);

	float l, t, r, b;

	getBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	draw(x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 32);
}


RECT GameObject::getBoundingBox()
{
	return {};
}

void GameObject::update(DWORD dt, vector<LPObject>* coObjects)
{
	this->dt = dt;
	dx = speed.vx * dt;
	dy = speed.vy * dt;
}

GameObject::~GameObject()
{
	texture = 0;
	animations.clear();
	//if (texture != NULL) texture->Release();
}
