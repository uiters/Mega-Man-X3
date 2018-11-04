#ifndef _StaticObject_H_
#define _StaticObject_H_

#include "GameObject.h"
#include "ConstGlobals.h"

class StaticObject 
	: public GameObject
{
protected:
	bool _canBreak;
public:
	StaticObject() {}
	StaticObject(UINT idTexture, float x, float y);
	~StaticObject() {}
	bool canBreak();
};

#endif // !_StaticObject_H_
