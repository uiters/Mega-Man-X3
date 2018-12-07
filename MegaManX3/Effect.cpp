#include "Effect.h"



Effect::Effect(int idTexture, int x, int y, int loop) : GameObject(idTexture, x, y)
{
	this->loop = loop;
}

Effect::~Effect()
{
}
