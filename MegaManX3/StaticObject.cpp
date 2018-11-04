#include "StaticObject.h"

StaticObject::StaticObject(UINT idTexture, float x, float y) : GameObject(idTexture, x, y) {}

bool StaticObject::canBreak()
{
	return _canBreak;
}
