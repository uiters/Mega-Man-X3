#include "StaticObject.h"

StaticObject::StaticObject(UINT idTexture, float x, float y) : GameObject(idTexture, idTexture, x, y, 0, 0) {
}

bool StaticObject::canBreak()
{
	return _canBreak;
}
