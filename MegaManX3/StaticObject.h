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
	int width;
	int height;
	StaticObject() {}
	~StaticObject() {}


	StaticObject(UINT id, float x, float y, int width, int height);
	bool canBreak();
	virtual void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void loadResources() override {}
	virtual void run() {}
};

#endif // !_StaticObject_H
