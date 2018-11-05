#ifndef _StaticObject_H
#define _StaticObject_H

#include "GameObject.h"
#include "ConstGlobals.h"

class StaticObject 
	: public GameObject
{
protected:
	bool _canBreak = false;
public:
	StaticObject() {}
	StaticObject(UINT idTexture, float x, float y);
	~StaticObject() {}
	bool canBreak();
};

#endif // !_StaticObject_H
