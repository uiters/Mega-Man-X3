#include "GameObject.h"
#include "Game.h"
//GameObject::_count = 0;
GameObject::GameObject(UINT idTexture, float x, float y, UINT width , UINT height) {
	this->x = x;
	this->y = y;

	this->width = width;
	this->height = height;
	this->_id = idTexture;

	//this->texture = CTextures::GetInstance()->Get(idTexture);

}

void GameObject::getSize(float & width, float & height)
{
	width = this->width;
	height = this->height;
}

RECT GameObject::getBound()
{
	return { (long)x, (long)y, (long)(x + width), (long)(y + height) };
}

GameObject::~GameObject()
{
	//if (texture != NULL) texture->Release();
}
